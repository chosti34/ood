#pragma once
#include <functional>

template <typename Style>
class IStyleEnumerator
{
public:
	virtual ~IStyleEnumerator() = default;
	virtual void Enumerate(std::function<void(Style&)> && callback) = 0;
};
