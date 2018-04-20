#pragma once
#include "IImageFileStorage.h"
#include <unordered_map>
#include <unordered_set>

/*
Класс с помощью которого можно копировать картинки
в рабочую директорию картинок документа
*/
class ImageFileStorage : public IImageFileStorage
{
public:
	ImageFileStorage();
	~ImageFileStorage();

	std::string AddImage(const std::string& imagePath) override;
	void Delete(const std::string& path) override;

	void CopyTo(const std::string& documentPath)const override;
	void SetCopyFlag(const std::string& filePath, bool copy) override;

private:
	std::unordered_set<std::string> m_imagePaths;
	std::string m_directory;
};
