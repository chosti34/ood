#pragma once
#include <boost/optional.hpp>
#include <memory>

// Пока вот так =)
class Path
{
public:
};

/*
Интерфейс изображения
*/
class IImage
{
public:
	// Возвращает путь относительно каталога документа
	virtual Path GetPath()const = 0;

	// Ширина изображения в пикселях
	virtual int GetWidth()const = 0;
	// Высота изображения в пикселях
	virtual int GetHeight()const = 0;

	// Изменяет размер изображения
	virtual void Resize(int width, int height) = 0;

	virtual ~IImage() = default;
};

/*
Интерфейс параграфа
*/
class IParagraph
{
public:
	virtual std::string GetText()const = 0;
	virtual void SetText(const std::string& text) = 0;
	virtual ~IParagraph() = default;
};

/*
Неизменяемый элемент документа
*/
class CConstDocumentItem
{
public:
	// Возвращает указатель на константное изображение, либо nullptr,
	// если элемент не является изображением
	std::shared_ptr<const IImage> GetImage()const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph()const;
	virtual ~CConstDocumentItem() = default;
};

/*
Элемент документа. Позволяет получить доступ к изображению или параграфу
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph();
};

/*
Интерфейс документа
*/
class IDocument
{
public:
	// Вставляет параграф текста в указанную позицию (сдвигая последующие элементы)
	// Если параметр position не указан, вставка происходит в конец документа
	virtual std::shared_ptr<IParagraph> InsertParagraph(
		const std::string& text, boost::optional<size_t> position = boost::none) = 0;

	// Вставляет изображение в указанную позицию (сдвигая последующие элементы)
	// Параметр path задает путь к вставляемому изображению
	// При вставке изображение должно копироваться в подкаталог images
	// под автоматически сгенерированным именем
	virtual std::shared_ptr<IImage> InsertImage(
		const Path& path, int width, int height, boost::optional<size_t> position = boost::none) = 0;

	// Возвращает количество элементов в документе
	virtual size_t GetItemsCount()const = 0;

	// Доступ к элементам изображения
	virtual CConstDocumentItem GetItem(size_t index)const = 0;
	virtual CDocumentItem GetItem(size_t index) = 0;

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

	// Сохраняет документ в формате html. Изображения сохраняются в подкаталог images.
	// Пути к изображениям указываются относительно пути к сохраняемому HTML файлу
	virtual void Save(const Path& path)const = 0;

	virtual ~IDocument() = default;
};
