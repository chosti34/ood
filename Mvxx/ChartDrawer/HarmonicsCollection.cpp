#include "stdafx.h"
#include "HarmonicsCollection.h"

SignalConnection HarmonicsCollection::DoOnHarmonicInsertion(InsertionSignal::slot_type slot)
{
	return m_insertionSignal.connect(slot);
}

SignalConnection HarmonicsCollection::DoOnHarmonicDeletion(DeletionSignal::slot_type slot)
{
	return m_deletionSignal.connect(slot);
}

SignalConnection HarmonicsCollection::DoOnHarmonicPropertiesChange(PropertiesChangeSignal::slot_type slot)
{
	return m_propertiesChangeSignal.connect(slot);
}

void HarmonicsCollection::InsertHarmonic(const Harmonic& harmonic, size_t index)
{
	if (index < m_harmonics.size())
	{
		m_harmonics.insert(m_harmonics.begin() + index, harmonic);
	}
	else
	{
		m_harmonics.push_back(harmonic);
	}
	m_insertionSignal();
}

void HarmonicsCollection::DeleteHarmonic(size_t index)
{
	if (m_harmonics.empty())
	{
		throw std::out_of_range("can't delete harmonic from empty collection");
	}

	if (index < m_harmonics.size())
	{
		m_harmonics.erase(m_harmonics.begin() + index);
	}
	else
	{
		m_harmonics.pop_back();
	}
	m_deletionSignal();
}

void HarmonicsCollection::SetHarmonic(const Harmonic& harmonic, size_t index)
{
	if (index >= m_harmonics.size())
	{
		throw std::out_of_range("index must be less than items count");
	}
	m_harmonics[index] = harmonic;
	m_propertiesChangeSignal(index);
}

float HarmonicsCollection::CalculateValue(float x)const
{
	if (m_harmonics.empty())
	{
		throw std::logic_error("can't calculate harmonics collection value");
	}

	float value = 0.f;
	for (const auto& harmonic : m_harmonics)
	{
		value += harmonic.CalculateValue(x);
	}
	return value;
}

const Harmonic& HarmonicsCollection::GetHarmonic(size_t index)const
{
	if (index >= m_harmonics.size())
	{
		throw std::out_of_range("index must be les than items count");
	}
	return m_harmonics[index];
}

size_t HarmonicsCollection::GetCount()const
{
	return m_harmonics.size();
}
