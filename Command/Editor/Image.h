#pragma once
#include "IImage.h"
#include "ICommandManager.h"

class Image : public IImage
{
public:
	Image(const std::string& path, unsigned width, unsigned height, ICommandManager& manager);

	std::string GetPath()const override;
	unsigned GetWidth()const override;
	unsigned GetHeight()const override;
	void Resize(unsigned width, unsigned height) override;

private:
	std::string m_path;
	unsigned m_width;
	unsigned m_height;
	ICommandManager& m_manager;
};
