#pragma once
#include "IDocument.h"
#include "DocumentCommandManager.h"
#include "IDocumentControl.h"
#include <deque>

class Document
	: public IDocument
	, private IDocumentControl
{
public:
	Document(const std::string& title = "untitled");

	void InsertParagraph(const std::string& text, boost::optional<size_t> position) override;
	void InsertImage(const std::string& path, unsigned width, unsigned height, boost::optional<size_t> position) override;
	void RemoveItem(size_t position) override;
	void ReplaceText(const std::string& text, size_t position) override;
	void ResizeImage(unsigned width, unsigned height, size_t position) override;
	void SetTitle(const std::string& title) override;

	std::string GetTitle()const override;
	size_t GetItemsCount()const override;
	std::shared_ptr<DocumentItem> GetItem(size_t index) override;
	std::shared_ptr<const DocumentItem> GetItem(size_t index)const override;

	bool CanUndo()const override;
	void Undo() override;

	bool CanRedo()const override;
	void Redo() override;

private:
	template <typename Command, typename... Args>
	void DoCommand(Args&&... args);

	void DoInsertItem(const std::shared_ptr<DocumentItem>& item, boost::optional<size_t> position) override;
	std::shared_ptr<DocumentItem> DoRemoveItem(boost::optional<size_t> index) override;
	void DoSetTitle(const std::string& title) override;
	void DoReplaceText(const std::string& text, size_t index) override;
	void DoResizeImage(unsigned width, unsigned height, size_t index) override;

private:
	std::string m_title;
	std::deque<std::shared_ptr<DocumentItem>> m_items;
	DocumentCommandManager m_commandManager;
};

template <typename Command, typename... Args>
inline void Document::DoCommand(Args&&... args)
{
	auto command = std::make_unique<Command>(args...);
	command->Execute(*this);
	m_commandManager.RegisterCommand(std::move(command));
}
