#pragma once
#include "IDocumentCommand.h"
#include <utility>

class ResizeImageCommand : public IDocumentCommand
{
	using Size = std::pair<unsigned, unsigned>;

public:
	ResizeImageCommand(const Size& newSize, const Size& oldSize, size_t index);

	void Execute(IDocumentCommandControl& control) override;
	void Unexecute(IDocumentCommandControl& control) override;

private:
	Size m_newSize;
	Size m_oldSize;
	size_t m_index;
};
