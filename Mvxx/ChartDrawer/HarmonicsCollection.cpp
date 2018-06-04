#include "stdafx.h"
#include "HarmonicsCollection.h"

void HarmonicsCollection::InsertHarmonic(const Harmonic& harmonic, size_t index)
{
	auto position = index < m_harmonics.size() ? m_harmonics.begin() + index : m_harmonics.end();
	m_harmonics.insert(position, harmonic);
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
}

void HarmonicsCollection::SetHarmonic(const Harmonic& harmonic, size_t index)
{
	if (index >= m_harmonics.size())
	{
		throw std::out_of_range("index must be les than items count");
	}
	m_harmonics[index] = harmonic;
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
		value += harmonic.GetValue(x);
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
