#pragma once
#include "IDocument.h"
#include "IDocumentCommand.h"
#include "DocumentCommandManager.h"
#include <vector>

class Document : public IDocument
{
public:
	Document();

	bool DoCommand(IDocumentCommandPtr&& command);

	std::shared_ptr<IParagraph> InsertParagraph(
		const std::string& text, boost::optional<size_t> position = boost::none) override;

	std::shared_ptr<IImage> InsertImage(
		const std::string& path, int width, int height, boost::optional<size_t> position = boost::none) override;

	size_t GetItemsCount()const override;
	std::shared_ptr<DocumentItem> GetItem(size_t index) override;
	std::shared_ptr<const DocumentItem> GetItem(size_t index)const override;

	void DeleteItem(size_t index) override;

	void SetTitle(const std::string& title) override;
	std::string GetTitle()const override;

	bool CanUndo()const override;
	void Undo() override;

	bool CanRedo()const override;
	void Redo() override;

private:
	std::string m_title;
	std::vector<std::shared_ptr<DocumentItem>> m_items;
	DocumentCommandManager m_commandManager;
};
