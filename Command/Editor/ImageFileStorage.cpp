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

void CopyFilesIntoDirectory(const std::unordered_set<std::string>& filePaths, const fs::path& to)
{
	if (DirectoryExists(to))
	{
		throw std::runtime_error("folder '" + to.generic_string() + "' already exists");
	}

	CreateDirectory(to);
	for (const auto& filePath : filePaths)
	{
		assert(fs::exists(filePath));
		assert(fs::is_regular_file(filePath));
		fs::copy(filePath, to / fs::path(filePath).filename());
	}
}
}

ImageFileStorage::ImageFileStorage()
	: m_directory("images")
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

	m_imagePaths.insert(m_directory + "/" + generatedFileName);
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
	m_imagePaths.erase(path);
}

void ImageFileStorage::CopyTo(const std::string& documentPath)const
{
	// Нет смысла копировать картинки если список файлов для копирования пуст
	//  или рабочая директория не была создана
	if (DirectoryExists(m_directory) && !m_imagePaths.empty())
	{
		CopyFilesIntoDirectory(m_imagePaths, fs::path(documentPath).parent_path() / m_directory);
	}
}

void ImageFileStorage::SetCopyFlag(const std::string& filePath, bool copy)
{
	if (copy)
	{
		m_imagePaths.insert(filePath);
	}
	else
	{
		m_imagePaths.erase(filePath);
	}
}
