#pragma once
#include <string>
#include <unordered_map>

/*
Класс с помощью которого можно копировать картинки
в рабочую директорию картинок документа
*/
class ImageFileStorage
{
public:
	ImageFileStorage();

	// Возвращает путь до картинки с новым сгенерированным именем
	std::string AddImage(const std::string& imagePath);

	// Удалить картинку по заданному пути
	void Delete(const std::string& path);

	// Скопировать все файлы картинок в папку где хранится файл документа
	void CopyTo(const std::string& documentPath);

	// Указываем, нужно ли копировать файл при сохранении документа
	void SetCopyFlag(const std::string& filePath, bool copy);

private:
	std::unordered_map<std::string, bool> m_copyFileFlags;
	std::string m_directory;
};
