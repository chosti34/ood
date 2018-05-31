#pragma once
#include <wx/panel.h>
#include <wx/listbox.h>
#include <wx/button.h>

#include "Harmonic.h"
#include "HarmonicSelectionPanel.h"
#include "HarmonicEditorPanel.h"
#include "HarmonicViewPanel.h"

class MainPanel : public wxPanel
{
public:
	MainPanel(wxFrame* frame);

private:
	std::vector<Harmonic> m_harmonics;

	HarmonicSelectionPanel* m_selectionPanel;
	HarmonicEditorPanel* m_editorPanel;
	HarmonicViewPanel* m_viewPanel;

	boost::signals2::scoped_connection m_harmonicSelectionConnection;
	boost::signals2::scoped_connection m_harmonicDeletionConnection;
	boost::signals2::scoped_connection m_harmonicInsertionConnection;
};
