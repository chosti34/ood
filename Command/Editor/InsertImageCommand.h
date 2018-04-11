#pragma once
#include "IDocumentCommand.h"
#include "IImageFileStorage.h"
#include <boost/optional.hpp>
#include <string>

class InsertImageCommand : public IDocumentCommand
{
public:
	InsertImageCommand(
		unsigned width, unsigned height,
		const std::string& path, boost::optional<size_t> position,
		IImageFileStorage& storage);

	void Execute(IDocumentCommandControl& control);
	void Unexecute(IDocumentCommandControl& control);

	~InsertImageCommand();

private:
	bool m_deleteFlag;
	unsigned m_width;
	unsigned m_height;
	std::string m_path;
	boost::optional<size_t> m_position;
	IImageFileStorage& m_storage;
};
