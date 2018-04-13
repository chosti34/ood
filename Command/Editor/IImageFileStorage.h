#pragma once
#include <string>

/*
Интерфейс хранилища картинок
*/
class IImageFileStorage
{
public:
	virtual ~IImageFileStorage() = default;

	// Возвращает путь до картинки с новым сгенерированным именем
	virtual std::string AddImage(const std::string& imagePath) = 0;

	// Удалить картинку по заданному пути
	virtual void Delete(const std::string& path) = 0;

	// Скопировать все файлы картинок в папку где хранится файл документа
	virtual void CopyTo(const std::string& documentPath)const = 0;

	// Указываем, нужно ли копировать файл при сохранении документа
	virtual void SetCopyFlag(const std::string& filePath, bool copyFlag) = 0;
};
