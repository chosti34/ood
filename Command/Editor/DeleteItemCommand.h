#pragma once
#include "IDocumentCommand.h"
#include "IDocumentCommandControl.h"
#include "IImageFileStorage.h"

class DeleteItemCommand : public IDocumentCommand
{
public:
	DeleteItemCommand(boost::optional<size_t>, IImageFileStorage& storage);

	void Execute(IDocumentCommandControl& control) override;
	void Unexecute(IDocumentCommandControl& control) override;

	~DeleteItemCommand();

private:
	bool m_deleteFlag;
	boost::optional<size_t> m_index;
	std::shared_ptr<DocumentItem> m_deletedItem;
	IImageFileStorage& m_storage;
};
