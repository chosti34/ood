#pragma once
#include "../IImageFileStorage.h"

class ImageFileStorageMock : public IImageFileStorage
{
public:
	virtual std::string AddImage(const std::string& imagePath) override { return imagePath; }
	virtual void Delete(const std::string& path) override {}
	virtual void CopyTo(const std::string& documentPath) const override {}
	virtual void SetCopyFlag(const std::string& filePath, bool copyFlag) override {}
};
