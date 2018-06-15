#include "stdafx.h"
#include "Harmonic.h"

Harmonic::Harmonic(float amplitude, float frequency, float phase, HarmonicType type)
	: m_amplitude(amplitude)
	, m_frequency(frequency)
	, m_phase(phase)
	, m_type(type)
{
}

float Harmonic::CalculateValue(float x) const
{
	float(*fn)(float) = (m_type == HarmonicType::Sin) ? std::sinf : std::cosf;
	return m_amplitude * fn(m_frequency * x + m_phase);
}

float Harmonic::GetAmplitude() const
{
	return m_amplitude;
}

void Harmonic::SetAmplitude(float amplitude)
{
	m_amplitude = amplitude;
}

float Harmonic::GetFrequency() const
{
	return m_frequency;
}

void Harmonic::SetFrequency(float frequency)
{
	m_frequency = frequency;
}

float Harmonic::GetPhase() const
{
	return m_phase;
}

void Harmonic::SetPhase(float phase)
{
	m_phase = phase;
}

HarmonicType Harmonic::GetType() const
{
	return m_type;
}

void Harmonic::SetType(HarmonicType type)
{
	m_type = type;
}
