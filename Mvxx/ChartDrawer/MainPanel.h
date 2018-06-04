#pragma once
#include "HarmonicSelectionView.h"
#include "HarmonicPropertiesView.h"
#include "HarmonicCanvasView.h"
#include <wx/panel.h>

class MainPanel : public wxPanel
{
public:
	MainPanel(wxFrame* frame);

	HarmonicSelectionView* GetSelectionView();
	HarmonicPropertiesView* GetPropertiesView();
	HarmonicCanvasView* GetCanvasView();

private:
	HarmonicSelectionView* m_selectionView;
	HarmonicPropertiesView* m_propertiesView;
	HarmonicCanvasView* m_canvasView;
};
