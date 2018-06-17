#pragma once
#include <wx/window.h>
#include <vector>

namespace SharedUI
{
extern const unsigned FLOAT_PRECISION;
extern const wxRealPoint PIXELS_PER_UNIT;
wxBoxSizer* AlignElements(const std::vector<wxWindow*>&& elements, int topOffset);
}
