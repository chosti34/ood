#pragma once
#include "IDocument.h"
#include "ICommand.h"

class Document : public IDocument
{
public:

	void OnCommand(std::unique_ptr<ICommand> && command);

	// Inherited via IDocument
	virtual std::shared_ptr<IParagraph> InsertParagraph(const std::string & text, boost::optional<size_t> position = boost::none) override;
	virtual std::shared_ptr<IImage> InsertImage(const Path & path, int width, int height, boost::optional<size_t> position = boost::none) override;
	virtual size_t GetItemsCount() const override;
	virtual CConstDocumentItem GetItem(size_t index) const override;
	virtual CDocumentItem GetItem(size_t index) override;
	virtual void DeleteItem(size_t index) override;
	virtual std::string GetTitle() const override;
	virtual void SetTitle(const std::string & title) override;
	virtual bool CanUndo() const override;
	virtual void Undo() override;
	virtual bool CanRedo() const override;
	virtual void Redo() override;
	virtual void Save(const Path & path) const override;
};
