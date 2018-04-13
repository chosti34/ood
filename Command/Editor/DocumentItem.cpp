#include "stdafx.h"
#include "DocumentItem.h"
#include "ReplaceTextCommand.h"
#include "ResizeImageCommand.h"

DocumentItem::DocumentItem(
	std::shared_ptr<IParagraph> paragraph,
	std::shared_ptr<IImage> image,
	ICommandManager& commandManager)
	: m_paragraph(paragraph)
	, m_image(image)
	, m_commandManager(commandManager)
{
}

std::shared_ptr<IParagraph> DocumentItem::GetParagraph()
{
	return m_paragraph;
}

std::shared_ptr<const IParagraph> DocumentItem::GetParagraph()const
{
	return m_paragraph;
}

std::shared_ptr<IImage> DocumentItem::GetImage()
{
	return m_image;
}

std::shared_ptr<const IImage> DocumentItem::GetImage()const
{
	return m_image;
}

void DocumentItem::ReplaceText(const std::string& text)
{
	if (!m_paragraph)
	{
		throw std::logic_error("trying to replace text on image element");
	}
	auto command = std::make_unique<ReplaceTextCommand>(*m_paragraph, text);
	command->Execute();
	m_commandManager.RegisterCommand(std::move(command));
}

void DocumentItem::ResizeImage(unsigned width, unsigned height)
{
	if (!m_image)
	{
		throw std::logic_error("trying to apply resize image command to paragraph");
	}
	auto command = std::make_unique<ResizeImageCommand>(*m_image, std::make_pair(width, height));
	command->Execute();
	m_commandManager.RegisterCommand(std::move(command));
}
