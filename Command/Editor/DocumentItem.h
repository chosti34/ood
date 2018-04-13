#pragma once
#include "IParagraph.h"
#include "IImage.h"
#include "ICommandManager.h"

/*
������� ���������. ����� �������� ��� ����������, ��� � ���������.
*/
class DocumentItem
{
public:
	DocumentItem(
		std::shared_ptr<IParagraph> paragraph,
		std::shared_ptr<IImage> image,
		ICommandManager& commandManager);

	// ���������� ��������� �� ��������, ���� ������� �������� ����������,
	//  ����� nullptr
	std::shared_ptr<IParagraph> GetParagraph();
	std::shared_ptr<const IParagraph> GetParagraph()const;

	// ���������� ��������� �� ��������, ���� ������� �������� ���������,
	//  ����� nullptr
	std::shared_ptr<IImage> GetImage();
	std::shared_ptr<const IImage> GetImage()const;

	// �������� ����� ���������,
	//  ����������� ���������� logic_error, ���� ������� �� �������� ����������
	void ReplaceText(const std::string& text);

	// �������� ������ ��������,
	//  ����������� ���������� logic_error, ���� ������� �� �������� ���������
	void ResizeImage(unsigned width, unsigned height);

private:
	// ��������� ������� ��������� ������ ���� ����� ��������� �������,
	//  ���, ��� � ���������, ����� ������ �� �������� ������
	ICommandManager& m_commandManager;
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};
