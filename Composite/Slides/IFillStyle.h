#pragma once
#include <cstdint>
#include <boost/optional.hpp>

class IFillStyle
{
public:
	virtual ~IFillStyle() = default;

	virtual boost::optional<bool> IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual boost::optional<uint32_t> GetColor()const = 0;
	virtual void SetColor(uint32_t color) = 0;
};
