#pragma once
#include "DocumentItem.h"
#include <boost/optional.hpp>

/*
Интерфейс документа
*/
class IDocument
{
public:
	// Вставить параграф в указанную позицию
	virtual void InsertParagraph(const std::string& text, boost::optional<size_t> position) = 0;

	// Вставить картинку в указанную позицию
	virtual void InsertImage(const std::string& path, unsigned width, unsigned height, boost::optional<size_t> position) = 0;

	// Удалить элемент находящийся по указанному индексу
	virtual void RemoveItem(size_t index) = 0;

	// Изменить текст в параграфе по указанному индексу
	virtual void ReplaceText(const std::string& text, size_t index) = 0;

	// Изменить размеры изображения по указанному индексу
	virtual void ResizeImage(unsigned width, unsigned height, size_t index) = 0;

	// Возвращает количество элементов в документе
	virtual size_t GetItemsCount()const = 0;

	// Доступ к элементам документа
	virtual std::shared_ptr<DocumentItem> GetItem(size_t index) = 0;
	virtual std::shared_ptr<const DocumentItem> GetItem(size_t index)const = 0;

	// Изменяет заголовок документа
	virtual void SetTitle(const std::string& title) = 0;

	// Возвращает заголовок документа
	virtual std::string GetTitle()const = 0;

	// Сообщает о доступности операции Undo
	virtual bool CanUndo()const = 0;
	// Отменяет команду редактирования
	virtual void Undo() = 0;

	// Сообщает о доступности операции Redo
	virtual bool CanRedo()const = 0;
	// Выполняет отменённую команду редактирования
	virtual void Redo() = 0;

	virtual ~IDocument() = default;
};
