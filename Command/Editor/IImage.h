#pragma once
#include <string>

class IImage
{
public:
	virtual ~IImage() = default;

	// Возвращает путь относительно каталога документа
	virtual std::string GetPath()const = 0;

	// Ширина изображения в пикселях
	virtual unsigned GetWidth()const = 0;
	// Высота изображения в пикселях
	virtual unsigned GetHeight()const = 0;

	// Изменяет размер изображения
	virtual void Resize(unsigned width, unsigned height) = 0;
};
