#include "stdafx.h"
#include "Harmonics.h"

Harmonics::Harmonics()
{
}

bool Harmonics::CalculateValue(float x, float& value)
{
	if (m_harmonics.empty())
	{
		return false;
	}

	value = 0.f;
	for (const auto& harmonic : m_harmonics)
	{
		value += harmonic.GetValue(x);
	}

	return true;
}

void Harmonics::InsertHarmonic(const Harmonic& harmonic)
{
	m_harmonics.push_back(harmonic);
	// send signal
}

bool Harmonics::DeleteHarmonicAt(int index)
{
	if (index >= 0 && index < m_harmonics.size())
	{
		m_harmonics.erase(m_harmonics.begin() + index);
		// send signal
		return true;
	}
	return false;
}

bool Harmonics::SetHarmonicAt(const Harmonic& harmonic, int index)
{
	if (index >= 0 && index < m_harmonics.size())
	{
		m_harmonics[index] = harmonic;
		// send signal
		return true;
	}
	return false;
}

const Harmonic& Harmonics::GetHarmonicAt(size_t index)const
{
	return m_harmonics[index];
}

size_t Harmonics::GetSize()const
{
	return m_harmonics.size();
}
