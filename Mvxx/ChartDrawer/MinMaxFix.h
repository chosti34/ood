#pragma once

#ifndef NOMINMAX
#define NOMINMAX
#endif

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

template <typename T1, typename T2>
auto max(T1 const& a, T2 const& b) -> decltype(a + b)
{
	return (a > b) ? a : b;
}

template <typename T1, typename T2>
auto min(T1 const& a, T2 const& b) -> decltype(a + b)
{
	return (a < b) ? a : b;
}
