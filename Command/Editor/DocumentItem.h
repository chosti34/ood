#pragma once
#include "IParagraph.h"
#include "IImage.h"
#include "ICommandManager.h"

/*
Элемент документа. Может являться как параграфом, так и картинкой.
*/
class DocumentItem
{
public:
	DocumentItem(
		std::shared_ptr<IParagraph> paragraph,
		std::shared_ptr<IImage> image,
		ICommandManager& commandManager);

	// Возвращает указатель на параграф, если элемент является параграфом,
	//  иначе nullptr
	std::shared_ptr<IParagraph> GetParagraph();
	std::shared_ptr<const IParagraph> GetParagraph()const;

	// Возвращает указатель на картинку, если элемент является картинкой,
	//  иначе nullptr
	std::shared_ptr<IImage> GetImage();
	std::shared_ptr<const IImage> GetImage()const;

	// Изменить текст параграфа,
	//  выбрасывает исключение logic_error, если элемент не является параграфом
	void ReplaceText(const std::string& text);

	// Изменить размер картинки,
	//  выбрасывает исключение logic_error, если элемент не является картинкой
	void ResizeImage(unsigned width, unsigned height);

private:
	// Поскольку элемент документа теперь тоже умеет создавать команды,
	//  ему, как и документу, нужна ссылка на менеджер команд
	ICommandManager& m_commandManager;
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};
