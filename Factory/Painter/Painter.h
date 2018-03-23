#pragma once
#include "IPainter.h"

class Painter : public IPainter
{
public:
	void DrawPicture(PictureDraft& draft, ICanvas& canvas) override;
};
