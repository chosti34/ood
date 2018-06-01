#include "stdafx.h"
#include "Harmonic.h"
#include <boost/format.hpp>
#include <functional>
#include <cmath>

Harmonic::Harmonic(float amplitude, float frequency, float phase, Type type)
	: amplitude(amplitude)
	, frequency(frequency)
	, phase(phase)
	, type(type)
{
}

float Harmonic::GetValue(float x)const
{
	std::function<float(float)> fn = type == Sin ? std::sinf : std::cosf;
	return amplitude * fn(frequency * x + phase);
}

std::string Harmonic::ToString()const
{
	return (boost::format("%1%*%2%(%3%*x + %4%)")
		% amplitude
		% (type == Sin ? "sin" : "cos")
		% frequency
		% phase).str();
}
