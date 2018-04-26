#pragma once
#include "IDocument.h"
#include "ICommandManager.h"
#include "ImageFileStorage.h"
#include <vector>

class Document : public IDocument
{
public:
	Document(const std::string& title,
		const std::shared_ptr<IImageFileStorage>& storage = std::make_shared<ImageFileStorage>("images"));

	void InsertParagraph(const std::string& text, boost::optional<size_t> position) override;
	void InsertImage(const std::string& path, unsigned width, unsigned height, boost::optional<size_t> position) override;
	void RemoveItem(size_t index) override;

	void ReplaceText(const std::string& text, size_t index) override;
	void ResizeImage(unsigned width, unsigned height, size_t index) override;

	void SetTitle(const std::string& title) override;
	std::string GetTitle()const override;

	size_t GetItemsCount()const override;
	std::shared_ptr<DocumentItem> GetItem(size_t index) override;
	std::shared_ptr<const DocumentItem> GetItem(size_t index)const override;

	bool CanUndo()const override;
	void Undo() override;

	bool CanRedo()const override;
	void Redo() override;

	void Save(const std::string& path)override;

private:
	std::string m_title;
	std::vector<std::shared_ptr<DocumentItem>> m_items;
	std::unique_ptr<ICommandManager> m_commandManager;
	std::shared_ptr<IImageFileStorage> m_storage;
};
