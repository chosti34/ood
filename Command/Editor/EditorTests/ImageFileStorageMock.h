#pragma once
#include "../IImageFileStorage.h"

//  ласс подмен€ющий хранилище файлов:
//  реальное удаление замен€етс€ выводом команды в поток выхода
class ImageFileStorageMock : public IImageFileStorage
{
public:
	ImageFileStorageMock(std::ostream* output = nullptr)
		: m_output(output)
	{
	}

	std::string AddImage(const std::string& imagePath)override
	{
		m_copyFlags.emplace(imagePath, true);
		return imagePath;
	}

	void Delete(const std::string& path)override
	{
		if (m_output)
		{
			*m_output << "Delete " << path;
		}
	}

	void CopyTo(const std::string& documentPath)const override
	{
		for (auto& pair : m_copyFlags)
		{
			auto& path = pair.first;
			auto& copyFlag = pair.second;
			if (m_output && copyFlag)
			{
				*m_output << path << " copied to " << documentPath;
			}
		}
	}

	void SetCopyFlag(const std::string& filePath, bool copyFlag)override
	{
		auto found = m_copyFlags.find(filePath);
		if (found != m_copyFlags.end())
		{
			found->second = copyFlag;
		}
	}

private:
	std::ostream* m_output;
	std::unordered_map<std::string, bool> m_copyFlags;
};
