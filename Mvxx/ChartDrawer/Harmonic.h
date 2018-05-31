#pragma once

class Harmonic
{
public:
	enum Type
	{
		Sin,
		Cos
	};

	Harmonic(
		float amplitude = 0.f,
		float frequency = 0.f,
		float phase = 0.f,
		Type type = Sin)
		: amplitude(amplitude)
		, frequency(frequency)
		, phase(phase)
		, type(type)
	{
	}

	std::string ToString()const
	{
		std::ostringstream strm;
		strm << amplitude << "*" << (type == Sin ? "sin" : "cos")
			<< "(" << frequency << "*x + " << phase << ")";
		return strm.str();
	}

	float amplitude;
	float frequency;
	float phase;
	Type type;
};
