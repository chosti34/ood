#pragma once
#include "DocumentItem.h"
#include <memory>

class IDocumentCommandControl
{
public:
	// �������� ������� �������� ��������� �� ���������� �������
	// ���� ������ �����������, �� ������� ��������� � �����
	virtual void DoInsertItem(const std::shared_ptr<DocumentItem>& item, boost::optional<size_t> position) = 0;

	// �������� �������� �������� �� ���������� �������,
	//  ���������� �������� Item
	virtual std::shared_ptr<DocumentItem> DoRemoveItem(boost::optional<size_t> position) = 0;

	// �������� ��������� ��������� ���������
	virtual void DoSetTitle(const std::string& title) = 0;

	// �������� ��������� ������ ���������
	virtual void DoReplaceText(const std::string& newText, size_t position) = 0;

	// �������� ��������� �������� �����������
	virtual void DoResizeImage(unsigned width, unsigned height, size_t position) = 0;

protected:
	~IDocumentCommandControl() = default;
};
