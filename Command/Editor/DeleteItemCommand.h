#pragma once
#include "IDocumentCommand.h"
#include "IDocumentControl.h"

class DeleteItemCommand : public IDocumentCommand
{
public:
	DeleteItemCommand(size_t index);

	void Execute(IDocumentControl& control) override;
	void Unexecute(IDocumentControl& control) override;

private:
	std::shared_ptr<DocumentItem> m_deletedItem;
	size_t m_index;
};
