#pragma once
#include <vector>
#include <wx/utils.h>

class ITableView
{
public:
	virtual ~ITableView() = default;
	virtual void SetPoints(const std::vector<wxRealPoint>& points) = 0;
};
