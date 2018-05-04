#pragma once
#include <cstdint>
#include <boost/optional.hpp>

class IOutlineStyle
{
public:
	virtual ~IOutlineStyle() = default;

	virtual boost::optional<bool> IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual boost::optional<uint32_t> GetColor()const = 0;
	virtual void SetColor(uint32_t color) = 0;

	virtual boost::optional<float> GetThickness()const = 0;
	virtual void SetThickness(float thickness) = 0;
};
