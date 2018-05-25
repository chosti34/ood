#include "stdafx.h"
#include "AddNewHarmonicDialog.h"
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/radiobut.h>
#include <wx/button.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/validate.h>
#include <wx/valtext.h>

wxString str;
wxTextValidator val(wxFILTER_ALPHA, &str);

AddNewHarmonicDialog::AddNewHarmonicDialog(const wxString& title)
	: wxDialog(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(280, 260), wxDEFAULT_DIALOG_STYLE | wxRESIZE_BORDER)
{
	/*wxPanel *panel = new wxPanel(this, -1);

	wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

	wxStaticBox *st = new wxStaticBox(panel, -1, wxT("Colors"),
		wxPoint(5, 5), wxSize(240, 150));
	m_rb = new wxRadioButton(panel, -1,
		wxT("256 Colors"), wxPoint(15, 30), wxDefaultSize, wxRB_GROUP);

	wxRadioButton *rb1 = new wxRadioButton(panel, -1,
		wxT("16 Colors"), wxPoint(15, 55));
	wxRadioButton *rb2 = new wxRadioButton(panel, -1,
		wxT("2 Colors"), wxPoint(15, 80));
	wxRadioButton *rb3 = new wxRadioButton(panel, -1,
		wxT("Custom"), wxPoint(15, 105));
	wxTextCtrl *tc = new wxTextCtrl(panel, -1, wxT(""),
		wxPoint(95, 105));

	wxButton *okButton = new wxButton(this, wxID_OK, wxT("Ok"),
		wxDefaultPosition, wxSize(70, 30));
	wxButton *closeButton = new wxButton(this, wxID_CANCEL, wxT("Cancel"),
		wxDefaultPosition, wxSize(70, 30));

	hbox->Add(okButton, 1);
	hbox->Add(closeButton, 1, wxLEFT, 5);

	vbox->Add(panel, 1);
	vbox->Add(hbox, 0, wxALIGN_CENTER | wxTOP | wxBOTTOM, 10);

	SetSizer(vbox);
*/
	//Connect();

	wxBoxSizer* harmonicEditorSizer = new wxBoxSizer(wxVERTICAL);
	wxPanel* harmonicEditorPanel = new wxPanel(this);
	//harmonicEditorPanel->Disable();
	//harmonicEditorPanel->SetBackgroundColour(wxColour(155, 155, 155));


	wxBoxSizer* hbox1 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* amplitudeTextLabel = new wxStaticText(harmonicEditorPanel, wxID_ANY, wxT("Amplitude:"));
	wxTextCtrl* amplitudeTextCtrl = new wxTextCtrl(harmonicEditorPanel, 4, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0,
		val);
	hbox1->Add(amplitudeTextLabel, 0, wxTOP | wxBOTTOM, 5);
	hbox1->Add(amplitudeTextCtrl, 0, wxTOP | wxBOTTOM, 5);
	harmonicEditorSizer->Add(hbox1, 0, wxALIGN_CENTER | wxTOP, 10);

	wxBoxSizer* hbox2 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* frequencyTextLabel = new wxStaticText(harmonicEditorPanel, wxID_ANY, wxT("Frequency:"));
	wxTextCtrl* frequenceTextCtrl = new wxTextCtrl(harmonicEditorPanel, 4);
	hbox2->Add(frequencyTextLabel, 0, wxTOP | wxBOTTOM, 5);
	hbox2->Add(frequenceTextCtrl, 0, wxTOP | wxBOTTOM, 5);
	harmonicEditorSizer->Add(hbox2, 0, wxALIGN_CENTER | wxTOP, 10);

	wxBoxSizer* hbox3 = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* phaseTextLabel = new wxStaticText(harmonicEditorPanel, wxID_ANY, wxT("Phase:"));
	wxTextCtrl* phaseTextCtrl = new wxTextCtrl(harmonicEditorPanel, 4);
	hbox3->Add(phaseTextLabel, 0, wxTOP | wxBOTTOM, 5);
	hbox3->Add(phaseTextCtrl, 0, wxTOP | wxBOTTOM, 5);
	harmonicEditorSizer->Add(hbox3, 0, wxALIGN_CENTER | wxTOP, 10);

	wxBoxSizer* hbox4 = new wxBoxSizer(wxHORIZONTAL);
	wxRadioButton* rbuttonSin = new wxRadioButton(harmonicEditorPanel, wxID_ANY, wxT("Sin"));
	wxRadioButton* rbuttonCos = new wxRadioButton(harmonicEditorPanel, wxID_ANY, wxT("Cos"));
	hbox4->Add(rbuttonSin, 0, wxTOP | wxBOTTOM, 5);
	hbox4->Add(rbuttonCos, 0, wxTOP | wxBOTTOM, 5);
	harmonicEditorSizer->Add(hbox4, 0, wxALIGN_CENTER | wxTOP, 10);

	wxBoxSizer *hbox = new wxBoxSizer(wxHORIZONTAL);

	wxButton *okButton = new wxButton(harmonicEditorPanel, wxID_OK, wxT("Add"),
		wxDefaultPosition, wxSize(70, 30));
	wxButton *closeButton = new wxButton(harmonicEditorPanel, wxID_CANCEL, wxT("Cancel"),
		wxDefaultPosition, wxSize(70, 30));

	hbox->Add(okButton, 1, wxALL, 5);
	hbox->Add(closeButton, 1, wxALL, 5);

	harmonicEditorSizer->Add(hbox, 0, wxALIGN_CENTER | wxTOP, 10);

	harmonicEditorPanel->SetSizer(harmonicEditorSizer);
	// harmonicEditorPanel->SetSizerAndFit(harmonicEditorSizer);
	//harmonicEditorPanel->SetSizer(harmonicEditorSizer);
	// harmonicEditorSizer->SetSizeHints(harmonicEditorPanel);
	//SetSize(harmonicEditorPanel->GetSize());
}
