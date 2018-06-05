#pragma once
#include "Harmonic.h"
#include "SignalAliases.h"
#include <climits>
#include <vector>

class HarmonicsCollection
{
public:
	SignalConnection DoOnHarmonicInsertion(SignalSlot slot);
	SignalConnection DoOnHarmonicDeletion(SignalSlot slot);

	void InsertHarmonic(const Harmonic& harmonic, size_t index = std::numeric_limits<size_t>::max());
	void DeleteHarmonic(size_t index = std::numeric_limits<size_t>::max());
	void SetHarmonic(const Harmonic& harmonic, size_t index);

	float CalculateValue(float x)const;
	const Harmonic& GetHarmonic(size_t index)const;
	size_t GetCount()const;

private:
	std::vector<Harmonic> m_harmonics;
	Signal m_insertionSignal;
	Signal m_deletionSignal;
};
