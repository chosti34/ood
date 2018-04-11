#pragma once
#include "IDocumentCommand.h"
#include "IDocumentCommandControl.h"
class ImageFileStorage;

class DeleteItemCommand : public IDocumentCommand
{
public:
	DeleteItemCommand(size_t index, ImageFileStorage& storage);

	void Execute(IDocumentCommandControl& control) override;
	void Unexecute(IDocumentCommandControl& control) override;

	~DeleteItemCommand();

private:
	bool m_deleteFlag;
	size_t m_index;
	std::shared_ptr<DocumentItem> m_deletedItem;
	ImageFileStorage& m_storage;
};
