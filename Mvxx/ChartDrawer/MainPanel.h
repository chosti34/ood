#pragma once
#include "Harmonic.h"
#include "HarmonicSelectionView.h"
#include "HarmonicPropertiesView.h"
#include "HarmonicCanvasView.h"
#include "HarmonicsCollection.h"
#include <wx/panel.h>
#include <memory>

class MainPanel : public wxPanel
{
public:
	MainPanel(wxFrame* frame);

	HarmonicSelectionView* GetSelectionPanel();
	HarmonicPropertiesView* GetEditorPanel();
	HarmonicCanvasView* GetViewPanel();

private:
	void CreateControls();
	void RegisterEventHandlers();

	std::vector<wxRealPoint> CalculatePoints(float lowerBound, float upperBound, float eps);

private:
	// TODO: store model outside of view
	std::vector<Harmonic> m_harmonics;

	std::shared_ptr<HarmonicsCollection> m_harmonicsX;

	HarmonicSelectionView* m_selectionPanel;
	HarmonicPropertiesView* m_editorPanel;
	HarmonicCanvasView* m_viewPanel;

	std::vector<boost::signals2::scoped_connection> m_connections;
};
