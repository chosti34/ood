#include "stdafx.h"
#include "MainPanel.h"

MainPanel::MainPanel(wxFrame* frame)
	: wxPanel(frame)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* upperSizer = new wxBoxSizer(wxHORIZONTAL);

	m_selectionView = new HarmonicSelectionView(this);
	upperSizer->Add(m_selectionView, 1, wxEXPAND | wxLEFT | wxTOP, 5);

	m_propertiesView = new HarmonicPropertiesView(this);
	upperSizer->Add(m_propertiesView, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);
	m_propertiesView->Disable();

	mainSizer->Add(upperSizer, 1, wxEXPAND, 0);
	m_canvasView = new HarmonicCanvasView(this);
	mainSizer->Add(m_canvasView, 1, wxEXPAND | wxALL, 5);

	SetSizerAndFit(mainSizer);
}

HarmonicSelectionView* MainPanel::GetSelectionView()
{
	return m_selectionView;
}

HarmonicPropertiesView* MainPanel::GetPropertiesView()
{
	return m_propertiesView;
}

HarmonicCanvasView* MainPanel::GetCanvasView()
{
	return m_canvasView;
}
