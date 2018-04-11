#pragma once
#include <string>

/*
����� � ������� �������� ����� ���������� ��������
� ������� ���������� �������� ���������
*/
class ImageFileStorage
{
public:
	ImageFileStorage(const std::string& directory);

	// ���������� ���� �� �������� � ����� ��������������� ������
	std::string AddImage(const std::string& imagePath)const;

	// ������� �������� �� ��������� ����
	void Delete(const std::string& path);

private:
	std::string m_directory;
};
