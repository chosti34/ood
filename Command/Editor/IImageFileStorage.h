#pragma once
#include <string>

/*
��������� ��������� ��������
*/
class IImageFileStorage
{
public:
	virtual ~IImageFileStorage() = default;

	// ���������� ���� �� �������� � ����� ��������������� ������
	virtual std::string AddImage(const std::string& imagePath) = 0;

	// ������� �������� �� ��������� ����
	virtual void Delete(const std::string& path) = 0;

	// ����������� ��� ����� �������� � ����� ��� �������� ���� ���������
	virtual void CopyTo(const std::string& documentPath)const = 0;

	// ���������, ����� �� ���������� ���� ��� ���������� ���������
	virtual void SetCopyFlag(const std::string& filePath, bool copyFlag) = 0;
};
