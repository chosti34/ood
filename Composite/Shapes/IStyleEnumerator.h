#pragma once
#include <functional>

template <typename Style>
class IStyleEnumerator
{
public:
	virtual ~IStyleEnumerator() = default;
	virtual void EnumerateStyles(std::function<void(Style&)> && callback) = 0;

	template <typename T>
	virtual boost::optional<T> GetProperty(std::function<Style&> && get) = 0;
};
