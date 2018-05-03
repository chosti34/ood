#pragma once
#include "../Shapes/ICanvasDrawable.h"
#include "Canvas.h"
#include <wx/panel.h>
#include <memory>
#include <vector>

class DrawingPanel : public wxPanel
{
public:
	DrawingPanel(wxFrame* frame);
	void AddDrawable(const std::shared_ptr<ICanvasDrawable>& drawable);

private:
	wxDECLARE_EVENT_TABLE();
	void OnPaint(wxPaintEvent& event);

private:
	std::vector<std::shared_ptr<ICanvasDrawable>> m_drawables;
};
