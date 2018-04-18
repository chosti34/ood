#pragma once
#include "DocumentItem.h"
#include <boost/optional.hpp>

class IDocument
{
public:
	virtual ~IDocument() = default;

	virtual void InsertParagraph(const std::string& text, boost::optional<size_t> position) = 0;
	virtual void InsertImage(const std::string& path, unsigned width, unsigned height,
		boost::optional<size_t> position) = 0;

	virtual void RemoveItem(size_t index) = 0;

	virtual void ReplaceText(const std::string& text, size_t index) = 0;
	virtual void ResizeImage(unsigned width, unsigned height, size_t index) = 0;

	virtual size_t GetItemsCount()const = 0;
	virtual std::shared_ptr<DocumentItem> GetItem(size_t index) = 0;
	virtual std::shared_ptr<const DocumentItem> GetItem(size_t index)const = 0;

	virtual void SetTitle(const std::string& title) = 0;
	virtual std::string GetTitle()const = 0;

	virtual bool CanUndo()const = 0;
	virtual void Undo() = 0;

	virtual bool CanRedo()const = 0;
	virtual void Redo() = 0;

	virtual void Save(const std::string& path) = 0;
};
