#include "stdafx.h"
#include "DocumentItem.h"

DocumentItem::DocumentItem(std::shared_ptr<IParagraph> paragraph, std::shared_ptr<IImage> image)
	: m_paragraph(paragraph)
	, m_image(image)
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
