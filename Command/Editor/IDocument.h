#pragma once
#include "DocumentItem.h"
#include "IDocumentCommand.h"
#include <boost/optional.hpp>
#include <memory>

class IDocument
{
public:
	virtual bool DoCommand(IDocumentCommandPtr&& command) = 0;

	// Вставляет параграф текста в указанную позицию (сдвигая последующие элементы)
	// Если параметр position не указан, вставка происходит в конец документа
	virtual std::shared_ptr<IParagraph> InsertParagraph(
		const std::string& text, boost::optional<size_t> position = boost::none) = 0;

	// Вставляет изображение в указанную позицию (сдвигая последующие элементы)
	// Параметр path задает путь к вставляемому изображению
	// При вставке изображение должно копироваться в подкаталог images
	// под автоматически сгенерированным именем
	virtual std::shared_ptr<IImage> InsertImage(
		const std::string& path, int width, int height, boost::optional<size_t> position = boost::none) = 0;

	// Возвращает количество элементов в документе
	virtual size_t GetItemsCount()const = 0;

	// Доступ к элементам документа
	virtual std::shared_ptr<DocumentItem> GetItem(size_t index) = 0;
	virtual std::shared_ptr<const DocumentItem> GetItem(size_t index)const = 0;

	// Удаляет элемент из документа
	virtual void DeleteItem(size_t index) = 0;

	// Возвращает заголовок документа
	virtual std::string GetTitle()const = 0;
	// Изменяет заголовок документа
	virtual void SetTitle(const std::string& title) = 0;

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
