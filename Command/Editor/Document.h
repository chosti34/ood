#pragma once
#include "IDocument.h"
#include "DocumentCommandManager.h"
#include "IDocumentCommandControl.h"
#include "IImageFileStorage.h"
#include <deque>

class Document
	: public IDocument
	, private IDocumentCommandControl
{
public:
	Document(IImageFileStorage& storage);
	Document(IImageFileStorage& storage, const std::string& title);

	// Методы, создающие команды
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

private:
	template <typename Command, typename... Args>
	void DoCommand(Args&&... args);

	// Методы, к которым будут обращаться команды
	void DoInsertItem(const std::shared_ptr<DocumentItem>& item, boost::optional<size_t> position) override;
	std::shared_ptr<DocumentItem> DoRemoveItem(boost::optional<size_t> index) override;
	void DoSetTitle(const std::string& title) override;
	void DoReplaceText(const std::string& text, size_t index) override;
	void DoResizeImage(unsigned width, unsigned height, size_t index) override;

private:
	std::string m_title;
	std::deque<std::shared_ptr<DocumentItem>> m_items;
	DocumentCommandManager m_commandManager;
	IImageFileStorage& m_storage;
};

template <typename Command, typename... Args>
inline void Document::DoCommand(Args&&... args)
{
	auto command = std::make_unique<Command>(args...);
	command->Execute(*this);
	m_commandManager.RegisterCommand(std::move(command));
}
