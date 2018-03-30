#pragma once

class ICanvas;
class PictureDraft;

class IPainter
{
public:
	virtual void DrawPicture(const PictureDraft& draft, ICanvas& canvas) = 0;
};
