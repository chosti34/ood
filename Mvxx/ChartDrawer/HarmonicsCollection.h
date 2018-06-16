#pragma once
#include "Harmonic.h"
#include "Signals.h"
#include <climits>
#include <vector>

class HarmonicsCollection
{
	using InsertionSignal = Signal<void()>;
	using DeletionSignal = Signal<void()>;
	using PropertiesChangeSignal = Signal<void(size_t)>;

public:
	SignalConnection DoOnHarmonicInsertion(InsertionSignal::slot_type slot);
	SignalConnection DoOnHarmonicDeletion(DeletionSignal::slot_type slot);
	SignalConnection DoOnHarmonicPropertiesChange(PropertiesChangeSignal::slot_type slot);

	void InsertHarmonic(const Harmonic& harmonic, size_t index = std::numeric_limits<size_t>::max());
	void DeleteHarmonic(size_t index = std::numeric_limits<size_t>::max());
	void SetHarmonic(const Harmonic& harmonic, size_t index);

	float CalculateValue(float x)const;
	const Harmonic& GetHarmonic(size_t index)const;
	size_t GetCount()const;

private:
	std::vector<Harmonic> m_harmonics;
	InsertionSignal m_insertionSignal;
	DeletionSignal m_deletionSignal;
	PropertiesChangeSignal m_propertiesChangeSignal;
};
