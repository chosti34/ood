#pragma once
#include "IImage.h"

class Image : public IImage
{
public:
	Image(const std::string& path, unsigned width, unsigned height);

	std::string GetPath()const override;
	int GetWidth()const override;
	int GetHeight()const override;
	void Resize(int width, int height) override;

private:
	std::string m_path;
	unsigned m_width;
	unsigned m_height;
};
