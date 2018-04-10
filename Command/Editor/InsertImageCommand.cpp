#include "stdafx.h"
#include "InsertImageCommand.h"
#include "Image.h"

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/random_generator.hpp>

namespace
{
const std::string IMAGES_DIRECTORY = "images";

std::string GenerateGuid()
{
	boost::uuids::uuid uuid = boost::uuids::random_generator()();
	return boost::lexical_cast<std::string>(uuid);
}

std::string CopyImageToImagesDirectory(const std::string& path)
{
	namespace fs = boost::filesystem;

	if (!fs::exists(path) || fs::is_directory(path))
	{
		throw std::invalid_argument("invalid path to image provided");
	}
	if (!fs::exists(IMAGES_DIRECTORY) || !fs::is_directory(IMAGES_DIRECTORY))
	{
		fs::create_directory(IMAGES_DIRECTORY);
	}

	const auto newPath = IMAGES_DIRECTORY + "/" + GenerateGuid() + fs::extension(path);
	fs::copy_file(path, newPath, fs::copy_option::fail_if_exists);
	return newPath;
}
}

InsertImageCommand::InsertImageCommand(
	unsigned width, unsigned height, const std::string& path, boost::optional<size_t> position)
	: m_width(width)
	, m_height(height)
	, m_path()
	, m_position(position)
	, m_deleteMark(true)
{
	assert(width >= 1u && width <= 10000u);
	assert(height >= 1u && height <= 10000u);
	m_path = CopyImageToImagesDirectory(path);
}

InsertImageCommand::~InsertImageCommand()
{
	if (m_deleteMark)
	{
		try
		{
			boost::filesystem::remove(m_path);
		}
		catch (...)
		{
			std::cout << "failed to remove " + m_path << std::endl;
		}
	}
}

void InsertImageCommand::Execute(IDocumentCommandControl& control)
{
	auto item = std::make_shared<DocumentItem>(nullptr, std::make_shared<Image>(m_path, m_width, m_height));
	control.DoInsertItem(item, m_position);
	m_deleteMark = false;
}

void InsertImageCommand::Unexecute(IDocumentCommandControl& control)
{
	control.DoRemoveItem(m_position);
	m_deleteMark = true;
}
