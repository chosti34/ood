#pragma once
#include <wx/utils.h>
#include <vector>

class ICanvasView
{
public:
	virtual ~ICanvasView() = default;
	virtual void SetPixelPoints(const std::vector<wxRealPoint>& points) = 0;
	virtual wxSize GetDrawingAreaSize()const = 0;
	virtual void UpdateDrawingAreaSize() = 0;
};
