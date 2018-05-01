#pragma once
#include <functional>
#include <boost/optional.hpp>

template <typename T>
boost::optional<T> GetCompositePropertyValueIfChildrenAreSame(
	size_t childrenCount, std::function<boost::optional<T>(size_t)> && getPropertyAtIndex)
{
	if (childrenCount == 0)
	{
		return boost::none;
	}

	boost::optional<T> value = getPropertyAtIndex(0);
	for (size_t i = 1; i < childrenCount; ++i)
	{
		if (value != getPropertyAtIndex(i))
		{
			return boost::none;
		}
	}
	return value;
}
