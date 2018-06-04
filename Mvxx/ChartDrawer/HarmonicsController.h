#pragma once
#include "MainFrame.h"
#include "HarmonicsCollection.h"

// ����� ����������� ��� ���������� ����� ��� ������ � ��� �������������,
//  ����� ��������� �� ��������������� �� ����������. � ������� �����������
//  ���������� ���������� ������ � �������������, ������� ������ ���� � �����
//  ����� �� ������. ����� �������, �������� ���� �������� - ������� ������ �������������
//  � ������, � ����� �� ������� ������������
class HarmonicsController
{
public:
	HarmonicsController(MainFrame* frame, const std::shared_ptr<HarmonicsCollection>& harmonics);

private:
	void OnHarmonicSelection(int index);
	void OnHarmonicDeletion(int index);
	void OnHarmonicInsertion(const Harmonic& harmonic);

private:
	MainFrame* m_frame;
	HarmonicSelectionView* m_selectionView;
	HarmonicPropertiesView* m_propertiesView;
	HarmonicCanvasView* m_canvasView;

	std::shared_ptr<HarmonicsCollection> m_harmonics;
	std::vector<boost::signals2::scoped_connection> m_connections;
};
