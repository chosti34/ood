#include "stdafx.h"
#include "MainPanel.h"

MainPanel::MainPanel(wxFrame* frame)
	: wxPanel(frame)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* upperSizer = new wxBoxSizer(wxHORIZONTAL);

	m_selectionPanel = new HarmonicSelectionView(this);
	upperSizer->Add(m_selectionPanel, 1, wxEXPAND | wxLEFT | wxTOP, 5);

	m_editorPanel = new HarmonicPropertiesView(this);
	upperSizer->Add(m_editorPanel, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);
	m_editorPanel->Disable();

	mainSizer->Add(upperSizer, 1, wxEXPAND, 0);
	m_viewPanel = new HarmonicCanvasView(this);
	mainSizer->Add(m_viewPanel, 1, wxEXPAND | wxALL, 5);

	SetSizerAndFit(mainSizer);
}

HarmonicSelectionView* MainPanel::GetSelectionPanel()
{
	return m_selectionPanel;
}

HarmonicPropertiesView* MainPanel::GetEditorPanel()
{
	return m_editorPanel;
}

HarmonicCanvasView* MainPanel::GetViewPanel()
{
	return m_viewPanel;
}
