#pragma once

template <typename T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
};

using RectF = Rect<float>;
