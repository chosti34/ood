#pragma once
#include <boost/signals2.hpp>

class Harmonic;

using HarmonicsListSignal = boost::signals2::signal<void(int)>;
using HarmonicSignal = boost::signals2::signal<void(const Harmonic&)>;
