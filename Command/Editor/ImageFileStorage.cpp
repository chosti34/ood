#include "stdafx.h"
#include "ImageFileStorage.h"
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;

namespace
{
bool DirectoryExists(const fs::path& path)
{
	boost::system::error_code code;

	bool exists = fs::exists(path, code);
	if (code.value() != boost::system::errc::success)
	{
		const std::string cause = ", code: " + std::to_string(code.value());
		throw std::runtime_error("failed to check existence of a directory" + cause);
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
}

ImageFileStorage::ImageFileStorage(const std::string& directory)
	: m_directory(directory)
{
}

std::string ImageFileStorage::AddImage(const std::string& imagePath)const
{
	if (!DirectoryExists(m_directory))
	{
		CreateDirectory(m_directory);
	}

	const auto generatedFileName = GenerateUniqueFileName() + fs::extension(imagePath);

	boost::system::error_code code;
	fs::copy_file(imagePath, m_directory + "/" + generatedFileName, code);
	if (code.value() != boost::system::errc::success)
	{
		throw std::runtime_error("failed to copy file, code: " + std::to_string(code.value()));
	}

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
}
