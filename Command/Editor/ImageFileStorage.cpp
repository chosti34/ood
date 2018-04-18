#include "stdafx.h"
#include "ImageFileStorage.h"
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>
#include <unordered_set>

namespace fs = boost::filesystem;

namespace
{
const std::unordered_set<std::string> IMAGE_EXTENSIONS = {
	".jpeg", ".jpg", ".gif", ".png", ".apng", ".svg", ".bmp"
};

bool DirectoryExists(const fs::path& path)
{
	boost::system::error_code code;

	bool exists = fs::exists(path, code);
	if (code.value() != boost::system::errc::success)
	{
		assert(!exists);
		return false;
	}

	bool isDirectory = fs::is_directory(path, code);
	if (code.value() != boost::system::errc::success)
	{
		const std::string cause = ", code: " + std::to_string(code.value());
		throw std::runtime_error("failed to whether the specified path is a directory" + cause);
	}

	return exists && isDirectory;
}

void CreateDirectory(const fs::path& path)
{
	boost::system::error_code code;
	fs::create_directory(path, code);
	if (code.value() != boost::system::errc::success)
	{
		throw std::runtime_error("failed to create a directory");
	}
}

std::string GenerateUniqueFileName()
{
	boost::system::error_code ec;
	auto newPath = boost::filesystem::unique_path("%%%%-%%%%-%%%%-%%%%", ec);
	if (ec != boost::system::errc::success)
	{
		throw std::runtime_error("failed to generate unique file name");
	}
	return newPath.string();
}

void RecursiveDirectoryContentCopy(const fs::path& from, const fs::path& to,
	const std::unordered_map<std::string, bool>& copyFlags)
{
	if (fs::exists(to))
	{
		throw std::runtime_error("folder \"" + from.generic_string() + "\" already exists");
	}

	if (fs::is_directory(from))
	{
		fs::create_directories(to);
		for (fs::directory_entry& item : fs::directory_iterator(from))
		{
			RecursiveDirectoryContentCopy(item.path(), to / item.path().filename(), copyFlags);
		}
	}
	else if (fs::is_regular_file(from))
	{
		auto found = copyFlags.find(from.generic_string());
		if (found != copyFlags.end() && found->second)
		{
			fs::copy(from, to);
		}
	}
	else
	{
		throw std::runtime_error(from.generic_string() + " is neither directory or file");
	}
}
}

ImageFileStorage::ImageFileStorage()
	: m_directory("images")
	, m_copyFileFlags()
{
	if (DirectoryExists(m_directory))
	{
		fs::remove_all(m_directory);
	}
}

ImageFileStorage::~ImageFileStorage()
{
	if (DirectoryExists(m_directory))
	{
		try
		{
			fs::remove_all(m_directory);
		}
		catch (...)
		{
		}
	}
}

std::string ImageFileStorage::AddImage(const std::string& imagePath)
{
	if (!DirectoryExists(m_directory))
	{
		CreateDirectory(m_directory);
	}

	const std::string extension = fs::extension(imagePath);
	if (IMAGE_EXTENSIONS.find(boost::algorithm::to_lower_copy(extension)) == IMAGE_EXTENSIONS.end())
	{
		throw std::invalid_argument("unsupported image extension");
	}

	const auto generatedFileName = GenerateUniqueFileName() + extension;

	boost::system::error_code code;
	fs::copy_file(imagePath, m_directory + "/" + generatedFileName, fs::copy_option::fail_if_exists, code);
	if (code.value() != boost::system::errc::success)
	{
		throw std::runtime_error("failed to copy file, code: " + std::to_string(code.value()));
	}

	m_copyFileFlags.emplace(m_directory + "/" + generatedFileName, true);
	return m_directory + "/" + generatedFileName;
}

void ImageFileStorage::Delete(const std::string& path)
{
	boost::system::error_code code;
	fs::remove(path, code);
	if (code.value() != boost::system::errc::success)
	{
		throw std::runtime_error("failed to delete file, code: " + std::to_string(code.value()));
	}
	m_copyFileFlags.erase(path);
}

void ImageFileStorage::CopyTo(const std::string& documentPath)const
{
	if (DirectoryExists(m_directory))
	{
		RecursiveDirectoryContentCopy(m_directory, fs::path(documentPath).parent_path() / m_directory, m_copyFileFlags);
	}
}

void ImageFileStorage::SetCopyFlag(const std::string& filePath, bool copy)
{
	auto found = m_copyFileFlags.find(filePath);
	if (found != m_copyFileFlags.end())
	{
		found->second = copy;
	}
}
