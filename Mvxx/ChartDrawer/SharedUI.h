#pragma once
#include <wx/window.h>
#include <vector>

namespace SharedUI
{
extern const unsigned FLOAT_PRECISION;
wxBoxSizer* AlignElements(const std::vector<wxWindow*>&& elements, int topOffset);
}
