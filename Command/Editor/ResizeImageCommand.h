#pragma once
#include "AbstractCommand.h"
#include "IImage.h"
#include <utility> // std::pair

class ResizeImageCommand final : public AbstractCommand
{
	using ImageSize = std::pair<unsigned, unsigned>;

public:
	ResizeImageCommand(IImage& image, const ImageSize& newSize);

private:
	void ExecuteImpl() override;
	void UnexecuteImpl() override;

private:
	IImage& m_image;
	ImageSize m_newSize;
	ImageSize m_oldSize;
};
