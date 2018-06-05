#pragma once
#include "HarmonicType.h"

class Harmonic
{
public:
	Harmonic() = default;
	Harmonic(float amplitude, float frequency, float phase, HarmonicType type);

	float CalculateValue(float x)const;

	float GetAmplitude()const;
	void SetAmplitude(float amplitude);

	float GetFrequency()const;
	void SetFrequency(float frequency);

	float GetPhase()const;
	void SetPhase(float phase);

	HarmonicType GetType()const;
	void SetType(HarmonicType type);

private:
	float m_amplitude = 0.f;
	float m_frequency = 0.f;
	float m_phase = 0.f;
	HarmonicType m_type = HarmonicType::Sin;
};
