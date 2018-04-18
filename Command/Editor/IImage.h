#pragma once
#include <string>

class IImage
{
public:
	virtual ~IImage() = default;
	virtual std::string GetPath()const = 0;
	virtual unsigned GetWidth()const = 0;
	virtual unsigned GetHeight()const = 0;
	virtual void Resize(unsigned width, unsigned height) = 0;
};
