#pragma once
#include "IPainter.h"

class Painter : public IPainter
{
public:
	void DrawPicture(const PictureDraft& draft, ICanvas& canvas) override;
};
