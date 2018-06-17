#include "stdafx.h"
#include "MainPanel.h"
#include <wx/notebook.h>
#include <wx/dataview.h>

MainPanel::MainPanel(wxFrame* frame)
	: wxPanel(frame)
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* upperSizer = new wxBoxSizer(wxHORIZONTAL);
	mainSizer->Add(upperSizer, 1, wxEXPAND, 0);

	m_selectionView = new HarmonicSelectionView(this);
	upperSizer->Add(m_selectionView, 1, wxEXPAND | wxLEFT | wxTOP, 5);

	m_propertiesView = new HarmonicPropertiesView(this);
	upperSizer->Add(m_propertiesView, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);
	m_propertiesView->Disable();

	wxNotebook* notebook = new wxNotebook(this, wxID_ANY, wxDefaultPosition, wxDefaultSize);
	mainSizer->Add(notebook, 1, wxEXPAND | wxALL, 5);

	m_canvasView = new HarmonicCanvasView(notebook);
	m_canvasView->SetDoubleBuffered(true);

	m_tableView = new HarmonicTableView(notebook);
	notebook->AddPage(m_canvasView, "Chart", true);
	notebook->AddPage(m_tableView, "Table", false);
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

HarmonicTableView* MainPanel::GetTableView()
{
	return m_tableView;
}
