#pragma once
#include <wx/panel.h>
#include "Harmonic.h"
#include "HarmonicSelectionPanel.h"
#include "HarmonicEditorPanel.h"
#include "HarmonicViewPanel.h"

class MainPanel : public wxPanel
{
public:
	MainPanel(wxFrame* frame);

private:
	void CreateControls();
	void RegisterEventHandlers();

private:
	// TODO: store model outside of view
	std::vector<Harmonic> m_harmonics;

	HarmonicSelectionPanel* m_selectionPanel;
	HarmonicEditorPanel* m_editorPanel;
	HarmonicViewPanel* m_viewPanel;

	std::vector<boost::signals2::scoped_connection> m_connections;
};
