#include "stdafx.h"
#include "MainPanel.h"

MainPanel::MainPanel(wxFrame* frame)
	: wxPanel(frame)
{
	wxBoxSizer* editorPartSizer = new wxBoxSizer(wxHORIZONTAL);

	m_selectionPanel = new HarmonicSelectionPanel(this);
	editorPartSizer->Add(m_selectionPanel, 1, wxEXPAND | wxLEFT | wxTOP, 5);

	m_editorPanel = new HarmonicEditorPanel(this);
	m_editorPanel->Disable();
	editorPartSizer->Add(m_editorPanel, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(editorPartSizer, 1, wxEXPAND, 0);

	m_viewPanel = new HarmonicViewPanel(this);
	mainSizer->Add(m_viewPanel, 1, wxEXPAND | wxALL, 5);

	SetSizerAndFit(mainSizer);

	m_harmonicSelectionConnection = m_selectionPanel->DoOnHarmonicSelection([this](int index) {
		assert(index >= 0 && index < m_harmonics.size());
		m_editorPanel->Enable();
		m_editorPanel->SetHarmonic(&m_harmonics[index]);
		m_editorPanel->TransferDataToWindow();
		std::cout << m_harmonics.size() << std::endl;
	});

	m_harmonicDeletionConnection = m_selectionPanel->DoOnHarmonicDeletion([this](int index) {
		assert(index >= 0 && index < m_harmonics.size());
		m_editorPanel->Disable();
		m_harmonics.erase(m_harmonics.begin() + index);
		std::cout << m_harmonics.size() << std::endl;
	});

	m_harmonicInsertionConnection = m_selectionPanel->DoOnHarmonicInsertion([this](const Harmonic& harmonic) {
		m_harmonics.push_back(harmonic);
		std::cout << m_harmonics.size() << std::endl;
	});
}
