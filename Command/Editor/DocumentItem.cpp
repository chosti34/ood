#include "stdafx.h"
#include "DocumentItem.h"
#include "ReplaceTextCommand.h"
#include "ResizeImageCommand.h"

DocumentItem::DocumentItem(
	std::shared_ptr<IParagraph> paragraph,
	std::shared_ptr<IImage> image)
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

std::string GetDescription(const DocumentItem& item)
{
	using std::to_string;

	const auto& paragraph = item.GetParagraph();
	const auto& image = item.GetImage();

	if (paragraph)
	{
		assert(!image);
		return "Paragraph: " + paragraph->GetText();
	}
	if (image)
	{
		assert(!paragraph);
		const auto& width = image->GetWidth();
		const auto& height = image->GetHeight();
		const auto& path = image->GetPath();
		return "Image: " + path + " " + to_string(width) + " " + to_string(height);
	}
	throw std::logic_error("document item is neither image or paragraph");
}
