#include "stdafx.h"
#include "MainPanel.h"
#include "AddHarmonicDlg.h"
#include "HarmonicSelectionPanel.h"
#include "HarmonicEditorPanel.h"
#include "HarmonicViewPanel.h"

MainPanel::MainPanel(wxFrame* frame)
	: wxPanel(frame)
{
	wxBoxSizer* editorPartSizer = new wxBoxSizer(wxHORIZONTAL);

	// Список добавленных гармоник
	HarmonicSelectionPanel* selection = new HarmonicSelectionPanel(this);
	editorPartSizer->Add(selection, 1, wxEXPAND | wxLEFT | wxTOP, 5);

	// Панель редактирования выбранной гармоники
	HarmonicEditorPanel* editor = new HarmonicEditorPanel(this);
	editor->Disable();
	editorPartSizer->Add(editor, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);

	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	mainSizer->Add(editorPartSizer, 1, wxEXPAND, 0);

	// Панель для отрисовки гармоники
	HarmonicViewPanel* view = new HarmonicViewPanel(this);
	mainSizer->Add(view, 1, wxEXPAND | wxALL, 5);

	SetSizerAndFit(mainSizer);
}
