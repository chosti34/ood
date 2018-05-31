#include "stdafx.h"
#include "MainPanel.h"

MainPanel::MainPanel(wxFrame* frame)
	: wxPanel(frame)
{
	CreateControls();
	RegisterEventHandlers();
}

void MainPanel::CreateControls()
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* upperSizer = new wxBoxSizer(wxHORIZONTAL);

	m_selectionPanel = new HarmonicSelectionPanel(this);
	upperSizer->Add(m_selectionPanel, 1, wxEXPAND | wxLEFT | wxTOP, 5);

	m_editorPanel = new HarmonicEditorPanel(this);
	upperSizer->Add(m_editorPanel, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);
	m_editorPanel->Disable();

	mainSizer->Add(upperSizer, 1, wxEXPAND, 0);
	m_viewPanel = new HarmonicViewPanel(this);
	mainSizer->Add(m_viewPanel, 1, wxEXPAND | wxALL, 5);

	SetSizerAndFit(mainSizer);
}

void MainPanel::RegisterEventHandlers()
{
	m_connections.push_back(m_selectionPanel->DoOnHarmonicSelection([this](int index) {
		assert(index >= 0 && index < m_harmonics.size());
		m_editorPanel->Enable();
		m_editorPanel->SetHarmonicData(m_harmonics[index]);
		std::cout << "Harmonics count: " << m_harmonics.size() << std::endl;
	}));

	m_connections.push_back(m_selectionPanel->DoOnHarmonicDeletion([this](int index) {
		assert(index >= 0 && index < m_harmonics.size());
		m_editorPanel->Disable();
		m_harmonics.erase(m_harmonics.begin() + index);
		std::cout << "Harmonics count: " << m_harmonics.size() << std::endl;
	}));

	m_connections.push_back(m_selectionPanel->DoOnHarmonicInsertion([this](const Harmonic& harmonic) {
		m_harmonics.push_back(harmonic);
		std::cout << "Harmonics count: " << m_harmonics.size() << std::endl;
	}));

	m_connections.push_back(m_editorPanel->DoOnHarmonicAttributesChange([this]() {
		int selection = m_selectionPanel->GetListBoxSelectionIndex();
		assert(selection != -1); // ��� ������� ������ � ������ �������������� ��������� ������ ���� ������� ������� ������
		m_selectionPanel->SetStringAtListBoxItem(m_editorPanel->GetHarmonicData().ToString(), selection);
		m_harmonics[selection] = m_editorPanel->GetHarmonicData();
	}));
}
