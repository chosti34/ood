#include "stdafx.h"
#include "Triangle.h"
#include <algorithm>
#include <vector>

Triangle::Triangle(const Point2D& vertex1, const Point2D& vertex2, const Point2D& vertex3)
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
}

RectF Triangle::GetFrame()const
{
	const float minX = std::min({ m_vertex1.x, m_vertex2.x, m_vertex3.x });
	const float maxX = std::max({ m_vertex1.x, m_vertex2.x, m_vertex3.x });
	const float width = maxX - minX;

	const float minY = std::min({ m_vertex1.y, m_vertex2.y, m_vertex3.y });
	const float maxY = std::max({ m_vertex1.y, m_vertex2.y, m_vertex3.y });
	const float height = maxY - minY;

	return RectF{ minX, minY, width, height };
}

void Triangle::SetFrame(const RectF& frame)
{
	std::vector<std::pair<float, float>> percentages;
	percentages.reserve(3);

	const auto oldFrame = GetFrame();
	for (const auto& point : {m_vertex1, m_vertex2, m_vertex3})
	{
		percentages.emplace_back(
			(point.x - oldFrame.left) / oldFrame.width, (point.y - oldFrame.top) / oldFrame.height);
	}

	m_vertex1 = { frame.left + percentages[0].first * frame.width, frame.top + percentages[0].second * frame.height };
	m_vertex2 = { frame.left + percentages[1].first * frame.width, frame.top + percentages[1].second * frame.height };
	m_vertex3 = { frame.left + percentages[2].first * frame.width, frame.top + percentages[2].second * frame.height };
}

const Point2D& Triangle::GetVertex1()const
{
	return m_vertex1;
}

const Point2D& Triangle::GetVertex2()const
{
	return m_vertex2;
}

const Point2D& Triangle::GetVertex3()const
{
	return m_vertex3;
}

void Triangle::StrokeDrawImpl(ICanvas& canvas)const
{
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}

void Triangle::FillDrawImpl(ICanvas& canvas)const
{
	canvas.FillPolygon({ m_vertex1, m_vertex2, m_vertex3 });
}
