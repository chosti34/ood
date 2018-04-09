#pragma once
#include "IDocumentCommand.h"
#include "IDocumentCommandControl.h"

class DeleteItemCommand : public IDocumentCommand
{
public:
	DeleteItemCommand(size_t index);

	void Execute(IDocumentCommandControl& control) override;
	void Unexecute(IDocumentCommandControl& control) override;

private:
	std::shared_ptr<DocumentItem> m_deletedItem;
	size_t m_index;
};
