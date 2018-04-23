#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include <boost/optional.hpp>
#include <string>

class InsertParagraphCommand final : public AbstractCommand
{
public:
	InsertParagraphCommand(
		boost::optional<size_t> index,
		const std::shared_ptr<IParagraph>& paragraph,
		std::vector<std::shared_ptr<DocumentItem>>& items);

private:
	void ExecuteImpl() override;
	void UnexecuteImpl() override;

private:
	boost::optional<size_t> m_index;
	std::shared_ptr<DocumentItem> m_item;
	std::vector<std::shared_ptr<DocumentItem>>& m_items;
};
