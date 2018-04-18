#pragma once
#include "AbstractCommand.h"
#include "IImage.h"
#include <functional>

class ResizeImageCommand final : public AbstractCommand
{
public:
	ResizeImageCommand(unsigned& width, unsigned& height, unsigned newWidth, unsigned newHeight);

private:
	void ExecuteImpl() override;
	void UnexecuteImpl() override;

private:
	unsigned& m_width;
	unsigned& m_height;
	unsigned m_newWidth;
	unsigned m_newHeight;
};
