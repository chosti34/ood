#include "stdafx.h"
#include "Painter.h"
#include "PictureDraft.h"

void Painter::DrawPicture(const PictureDraft& draft, ICanvas& canvas)
{
	for (const auto& shape : draft)
	{
		shape.Draw(canvas);
	}
}
