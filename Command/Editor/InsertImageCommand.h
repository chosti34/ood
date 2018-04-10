#pragma once
#include "IDocumentCommand.h"
#include <boost/optional.hpp>
#include <string>

class InsertImageCommand : public IDocumentCommand
{
public:
	InsertImageCommand(
		unsigned width, unsigned height, const std::string& path, boost::optional<size_t> position);
	~InsertImageCommand();

	void Execute(IDocumentCommandControl& control);
	void Unexecute(IDocumentCommandControl& control);

private:
	unsigned m_width;
	unsigned m_height;
	std::string m_path;
	boost::optional<size_t> m_position;
	bool m_deleteMark;
};
