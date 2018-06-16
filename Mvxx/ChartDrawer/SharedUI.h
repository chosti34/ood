#pragma once
#include <wx/textctrl.h>
#include <wx/string.h>
#include <wx/window.h>
#include <vector>

namespace SharedUI
{
extern const unsigned FLOAT_PRECISION;
wxBoxSizer* AlignElements(const std::vector<wxWindow*>&& elements, int topOffset);
}
