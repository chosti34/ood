#pragma once
#include <cstdint>
#include <boost/optional.hpp>

class IShapeStyle
{
public:
	virtual ~IShapeStyle() = default;

	virtual boost::optional<bool> IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual boost::optional<uint32_t> GetColor()const = 0;
	virtual void SetColor(boost::optional<uint32_t> color) = 0;

	virtual boost::optional<unsigned> GetThickness()const = 0;
	virtual void SetThickness(boost::optional<unsigned> thickness) = 0;
};
