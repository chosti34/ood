#pragma once
#include "IDocument.h"
#include "IDocumentCommand.h"

class Document : private IDocument
{
public:
	Document(const std::string& title);
	void OnCommand(std::unique_ptr<IDocumentCommand> && command);

	size_t GetItemsCount()const override;
	CConstDocumentItem GetItem(size_t index)const override;
	CDocumentItem GetItem(size_t index) override;

	std::string GetTitle()const override;

	bool CanUndo()const override;
	void Undo() override;
	bool CanRedo()const override;
	void Redo() override;

private:
	std::shared_ptr<IParagraph> InsertParagraph(
		const std::string& text, boost::optional<size_t> position = boost::none) override;
	std::shared_ptr<IImage> InsertImage(
		const Path& path, int width, int height, boost::optional<size_t> position = boost::none) override;

	void DeleteItem(size_t index) override;
	void SetTitle(const std::string& title) override;

	void Save(const Path& path)const override;

private:
	std::string m_title;
};
