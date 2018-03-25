#pragma once
#include "IDesigner.h"
#include "IShapeFactory.h"

class Designer : public IDesigner
{
public:
	Designer(IShapeFactory& factory);
	PictureDraft CreateDraft(std::istream& strm) override;

private:
	IShapeFactory & m_factory;
};
