#include "stdafx.h"
#include "Harmonic.h"

std::string ToString(const Harmonic& harmonic)
{
	std::ostringstream strm;
	strm << harmonic.amplitude << "*" << (harmonic.type == HarmonicType::Sin ? "sin" : "cos");
	strm << "(" << harmonic.frequency << "*x + " << harmonic.phase << ")" << std::endl;
	return strm.str();
}
