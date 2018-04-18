#pragma once
#include "AbstractCommand.h"
#include "IImageFileStorage.h"
#include "IImage.h"
#include "DocumentItem.h"
#include <boost/optional.hpp>
#include <string>

class InsertImageCommand final : public AbstractCommand
{
public:
	InsertImageCommand(
		boost::optional<size_t> index,
		std::shared_ptr<IImage> image,
		std::vector<std::shared_ptr<DocumentItem>>& items,
		std::shared_ptr<IImageFileStorage> storage);
	~InsertImageCommand();

private:
	void ExecuteImpl() override;
	void UnexecuteImpl() override;

private:
	boost::optional<size_t> m_index;
	std::shared_ptr<DocumentItem> m_item;
	std::vector<std::shared_ptr<DocumentItem>>& m_items;
	std::shared_ptr<IImageFileStorage> m_storage;
};
