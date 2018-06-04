#pragma once
#include "HarmonicSelectionView.h"
#include "HarmonicPropertiesView.h"
#include "HarmonicCanvasView.h"
#include <wx/panel.h>

class MainPanel : public wxPanel
{
public:
	MainPanel(wxFrame* frame);

	HarmonicSelectionView* GetSelectionPanel();
	HarmonicPropertiesView* GetEditorPanel();
	HarmonicCanvasView* GetViewPanel();

private:
	HarmonicSelectionView* m_selectionPanel;
	HarmonicPropertiesView* m_editorPanel;
	HarmonicCanvasView* m_viewPanel;
};
