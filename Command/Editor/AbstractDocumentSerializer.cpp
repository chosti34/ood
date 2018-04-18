#include "stdafx.h"
#include "AbstractDocumentSerializer.h"
#include "HTMLDocumentSerializer.h"
#include "XMLDocumentSerializer.h"
#include "JSONDocumentSerializer.h"
#include <boost/filesystem.hpp>

void AbstractDocumentSerializer::Serialize(const std::string& path)const
{
	std::ofstream output(path);
	if (!output)
	{
		throw std::runtime_error("failed to open file " + path + " for serializing");
	}
	SerializeImpl(output);
}

std::unique_ptr<AbstractDocumentSerializer> CreateSerializer(const std::string& path)
{
	const std::string extension = boost::filesystem::extension(path);
	if (extension == ".html")
	{
		return std::make_unique<HTMLDocumentSerializer>();
	}
	if (extension == ".xml")
	{
		return std::make_unique<XMLDocumentSerializer>();
	}
	if (extension == ".json")
	{
		return std::make_unique<JSONDocumentSerializer>();
	}
	throw std::runtime_error("can't create serializer with extension: \"" + extension + "\"");
}
