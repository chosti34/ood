#pragma once
#include <iosfwd>
#include "PictureDraft.h"

class IDesigner
{
public:
	virtual ~IDesigner() = default;
	virtual PictureDraft CreateDraft(std::istream& strm) = 0;
};
