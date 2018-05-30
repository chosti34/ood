#pragma once

enum class HarmonicType
{
	Sin,
	Cos
};

struct Harmonic
{
	float amplitude = 0.f;
	float phase = 0.f;
	float frequency = 0.f;
	HarmonicType type = HarmonicType::Sin;
};

std::string ToString(const Harmonic& harmonic);
