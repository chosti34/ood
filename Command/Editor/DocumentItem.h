#pragma once
#include "IParagraph.h"
#include "IImage.h"
#include <memory>

class DocumentItem
{
public:
	DocumentItem(std::shared_ptr<IParagraph> paragraph, std::shared_ptr<IImage> image);

	std::shared_ptr<IParagraph> GetParagraph();
	std::shared_ptr<const IParagraph> GetParagraph()const;

	std::shared_ptr<IImage> GetImage();
	std::shared_ptr<const IImage> GetImage()const;

private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};
