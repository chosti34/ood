#pragma once
#include "DocumentItem.h"
#include <memory>

class IDocumentCommandControl
{
public:
	// Операция вставки элемента документа по указанному индексу
	// Если индекс отсутствует, то вставка произойдёт в конец
	virtual void DoInsertItem(const std::shared_ptr<DocumentItem>& item, boost::optional<size_t> position) = 0;

	// Операция удаления элемента по указанному индексу,
	//  возвращает удалённый Item
	virtual std::shared_ptr<DocumentItem> DoRemoveItem(boost::optional<size_t> position) = 0;

	// Операция изменения заголовка документа
	virtual void DoSetTitle(const std::string& title) = 0;

	// Операция изменения текста параграфа
	virtual void DoReplaceText(const std::string& newText, size_t position) = 0;

	// Операция изменения размеров изображения
	virtual void DoResizeImage(unsigned width, unsigned height, size_t position) = 0;

protected:
	~IDocumentCommandControl() = default;
};
