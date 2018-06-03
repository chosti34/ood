#pragma once
#include "Harmonic.h"
#include "HarmonicSelectionPanel.h"
#include "HarmonicEditorPanel.h"
#include "HarmonicViewPanel.h"
#include "Harmonics.h"
#include <wx/panel.h>
#include <memory>

class MainPanel : public wxPanel
{
public:
	MainPanel(wxFrame* frame);

	void SetHarmonics(const std::shared_ptr<Harmonics>& harmonics);
	HarmonicSelectionPanel* GetSelectionPanel();
	HarmonicEditorPanel* GetEditorPanel();
	HarmonicViewPanel* GetViewPanel();

private:
	void CreateControls();
	void RegisterEventHandlers();

	std::vector<wxRealPoint> CalculatePoints(float lowerBound, float upperBound, float eps);

private:
	// TODO: store model outside of view
	std::vector<Harmonic> m_harmonics;

	std::shared_ptr<Harmonics> m_harmonicsX;

	HarmonicSelectionPanel* m_selectionPanel;
	HarmonicEditorPanel* m_editorPanel;
	HarmonicViewPanel* m_viewPanel;

	std::vector<boost::signals2::scoped_connection> m_connections;
};
