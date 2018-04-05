#pragma once

#include "IParagraph.h"
#include "IImage.h"

#include <memory>
#include <boost/optional.hpp>

class DocumentItem
{
public:
	DocumentItem(std::shared_ptr<IParagraph> paragraph, std::shared_ptr<IImage> image)
		: m_paragraph(paragraph)
		, m_image(image)
	{
	}

	std::shared_ptr<IParagraph> GetParagraph()
	{
		return m_paragraph;
	}

	std::shared_ptr<const IParagraph> GetParagraph()const
	{
		return m_paragraph;
	}

	std::shared_ptr<IImage> GetImage()
	{
		return m_image;
	}

	std::shared_ptr<const IImage> GetImage()const
	{
		return m_image;
	}

	std::string GetDescription()const
	{
		if (m_paragraph != nullptr)
		{
			return "Paragraph: " + m_paragraph->GetText();
		}
		else if (m_image != nullptr)
		{
			return "Image: " + std::to_string(m_image->GetWidth()) + " "
				+ std::to_string(m_image->GetHeight()) + " " + m_image->GetPath();
		}
		throw std::logic_error("DocumentItem is neither paragraph or image");
	}

private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};

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

	// Сохраняет документ в формате html. Изображения сохраняются в подкаталог images.
	// Пути к изображениям указываются относительно пути к сохраняемому HTML файлу
	virtual void Save(const std::string& path)const = 0;

	virtual ~IDocument() = default;
};
