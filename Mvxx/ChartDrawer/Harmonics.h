#pragma once
#include "Harmonic.h"
#include <vector>

class Harmonics
{
public:
	Harmonics();

	bool CalculateValue(float x, float& value);

	void InsertHarmonic(const Harmonic& harmonic);
	bool DeleteHarmonicAt(int index);
	bool SetHarmonicAt(const Harmonic& harmonic, int index);

	const Harmonic& GetHarmonicAt(size_t index)const;
	size_t GetSize()const;

private:
	std::vector<Harmonic> m_harmonics;
};
