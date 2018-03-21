#include "stdafx.h"
#include "Designer.h"
#include "Shape.h"

Designer::Designer(IShapeFactory& factory)
	: m_factory(factory)
{
}

PictureDraft Designer::CreateDraft(std::istream& strm)
{
	PictureDraft draft;
	std::string line;
	while (getline(strm, line))
	{
		draft.AddShape(std::move(m_factory.CreateShape(line)));
	}
	return draft;
}
