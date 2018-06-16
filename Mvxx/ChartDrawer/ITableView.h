#pragma once
#include <vector>
#include <string>

class ITableView
{
public:
	virtual ~ITableView() = default;
	virtual void AddRowValues(const std::vector<std::string>& values) = 0;
};
