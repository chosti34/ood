#pragma once
#include <string>

/*
 ласс с помощью которого можно копировать картинки
в рабочую директорию картинок документа
*/
class ImageFileStorage
{
public:
	ImageFileStorage(const std::string& directory);

	// ¬озвращает путь до картинки с новым сгенерированным именем
	std::string AddImage(const std::string& imagePath)const;

	// ”далить картинку по заданному пути
	void Delete(const std::string& path);

private:
	std::string m_directory;
};
