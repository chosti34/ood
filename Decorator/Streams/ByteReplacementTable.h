#pragma once
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

class ByteReplacementTable
{
public:
	ByteReplacementTable(unsigned seed)
		: m_table(256u)
		, m_reversedTable(256u)
	{
		std::iota(m_table.begin(), m_table.end(), 0u);
		std::shuffle(m_table.begin(), m_table.end(), std::mt19937(seed));
	}

private:
	std::vector<uint8_t> m_table;
	std::vector<uint8_t> m_reversedTable;
};
