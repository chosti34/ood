#pragma once

class Harmonic
{
public:
	enum Type
	{
		Sin,
		Cos
	};

	Harmonic(float amplitude = 0.f, float frequency = 0.f, float phase = 0.f, Type type = Sin);
	std::string ToString()const;

	float amplitude;
	float frequency;
	float phase;
	Type type;
};
