#pragma once
#include "IDocumentCommand.h"
#include "IDocument.h"

class DeleteItemCommand : public IDocumentCommand
{
public:
	DeleteItemCommand(size_t pos);

	bool Execute(IDocument& document) override;
	void Undo(IDocument& document) override;
	void Redo(IDocument& document) override;

private:
	size_t m_pos;
	std::shared_ptr<const DocumentItem> m_deletedItem;
};
