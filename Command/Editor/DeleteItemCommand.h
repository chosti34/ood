#pragma once
#include "AbstractCommand.h"
#include "IDocumentCommandControl.h"
#include "IImageFileStorage.h"

class DeleteItemCommand final : public AbstractCommand
{
public:
	DeleteItemCommand(
		IDocumentCommandControl& control,
		boost::optional<size_t> index,
		IImageFileStorage& storage);
	~DeleteItemCommand();

private:
	void ExecuteImpl() override;
	void UnexecuteImpl() override;

private:
	IDocumentCommandControl& m_control;
	bool m_imageDeletedFlag;
	boost::optional<size_t> m_index;
	std::shared_ptr<DocumentItem> m_deletedItem;
	IImageFileStorage& m_storage;
};
