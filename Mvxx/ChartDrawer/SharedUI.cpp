#include "stdafx.h"
#include "SharedUI.h"

namespace SharedUI
{
const unsigned FLOAT_PRECISION = 3;

wxBoxSizer* AlignElements(const std::vector<wxWindow*>&& elements, int topOffset)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	if (elements.size() == 0)
	{
		return sizer;
	}

	sizer->Add(elements.front(), 0, wxALIGN_LEFT);
	for (size_t i = 1; i < elements.size(); ++i)
	{
		sizer->Add(elements[i], 0, wxALIGN_LEFT | wxTOP, topOffset);
	}
	return sizer;
}
}
