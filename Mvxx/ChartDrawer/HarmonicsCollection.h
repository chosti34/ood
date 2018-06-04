#pragma once
#include "Harmonic.h"
#include <climits>
#include <vector>

class HarmonicsCollection
{
public:
	void InsertHarmonic(const Harmonic& harmonic, size_t index = std::numeric_limits<size_t>::max());
	void DeleteHarmonic(size_t index = std::numeric_limits<size_t>::max());
	void SetHarmonic(const Harmonic& harmonic, size_t index);

	float CalculateValue(float x)const;
	const Harmonic& GetHarmonic(size_t index)const;
	size_t GetCount()const;

private:
	std::vector<Harmonic> m_harmonics;
};
