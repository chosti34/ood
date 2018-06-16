#pragma once
#include "Signals.h"
#include <wx/utils.h>
#include <vector>

class ICanvasView
{
public:
	virtual ~ICanvasView() = default;
	virtual void SetPixelPoints(const std::vector<wxRealPoint>& points) = 0;
};
