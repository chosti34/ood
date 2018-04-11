#pragma once
#include "IDocumentCommand.h"
#include "IDocumentCommandControl.h"
#include "IImageFileStorage.h"

class DeleteItemCommand : public IDocumentCommand
{
public:
	DeleteItemCommand(size_t index, bool fromEnd, IImageFileStorage& storage);

	void Execute(IDocumentCommandControl& control) override;
	void Unexecute(IDocumentCommandControl& control) override;

	~DeleteItemCommand();

private:
	bool m_deleteFlag;
	bool m_fromEnd;
	size_t m_index;
	std::shared_ptr<DocumentItem> m_deletedItem;
	IImageFileStorage& m_storage;
};
