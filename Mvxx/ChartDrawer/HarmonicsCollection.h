#pragma once
#include "Harmonic.h"
#include <boost/signals2.hpp>
#include <climits>
#include <vector>

class HarmonicsCollection
{
public:
	boost::signals2::connection DoOnHarmonicInsertion(
		boost::signals2::signal<void()>::slot_type slot);
	boost::signals2::connection DoOnHarmonicDeletion(
		boost::signals2::signal<void()>::slot_type slot);

	void InsertHarmonic(const Harmonic& harmonic, size_t index = std::numeric_limits<size_t>::max());
	void DeleteHarmonic(size_t index = std::numeric_limits<size_t>::max());
	void SetHarmonic(const Harmonic& harmonic, size_t index);

	float CalculateValue(float x)const;
	const Harmonic& GetHarmonic(size_t index)const;
	size_t GetCount()const;

private:
	std::vector<Harmonic> m_harmonics;
	boost::signals2::signal<void()> m_insertionSignal;
	boost::signals2::signal<void()> m_deletionSignal;
};
