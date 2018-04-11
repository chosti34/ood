#pragma once
#include "IDocumentCommand.h"
#include <boost/optional.hpp>
#include <string>
class ImageFileStorage;

class InsertImageCommand : public IDocumentCommand
{
public:
	InsertImageCommand(
		unsigned width, unsigned height,
		const std::string& path, boost::optional<size_t> position,
		ImageFileStorage& storage);

	void Execute(IDocumentCommandControl& control);
	void Unexecute(IDocumentCommandControl& control);

	~InsertImageCommand();

private:
	bool m_deleteFlag;
	unsigned m_width;
	unsigned m_height;
	std::string m_path;
	boost::optional<size_t> m_position;
	ImageFileStorage& m_storage;
};
