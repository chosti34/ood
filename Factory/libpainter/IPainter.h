#pragma once

class ICanvas;
class PictureDraft;

class IPainter
{
public:
	virtual void DrawPicture(PictureDraft& draft, ICanvas& canvas) = 0;
};
