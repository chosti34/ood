#include "stdafx.h"
#include "Harmonic.h"
#include <boost/format.hpp>

Harmonic::Harmonic(float amplitude, float frequency, float phase, Type type)
	: amplitude(amplitude)
	, frequency(frequency)
	, phase(phase)
	, type(type)
{
}

std::string Harmonic::ToString() const
{
	return (boost::format("%1%*%2%(%3%*x + %4%)")
		% amplitude
		% (type == Sin ? "sin" : "cos")
		% frequency
		% phase).str();
}
