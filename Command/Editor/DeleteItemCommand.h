#pragma once
#include "AbstractCommand.h"
#include "IImageFileStorage.h"
#include "DocumentItem.h"

class DeleteItemCommand final : public AbstractCommand
{
public:
	DeleteItemCommand(
		size_t index,
		std::vector<std::shared_ptr<DocumentItem>>& items,
		const std::shared_ptr<IImageFileStorage>& storage);
	~DeleteItemCommand();

private:
	void ExecuteImpl() override;
	void UnexecuteImpl() override;

private:
	size_t m_index;
	std::shared_ptr<DocumentItem> m_item;
	std::vector<std::shared_ptr<DocumentItem>>& m_items;
	std::shared_ptr<IImageFileStorage> m_storage;
	bool m_deleteImageFlag;
};
