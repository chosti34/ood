#include "stdafx.h"
#include "../IPainter.h"
#include "../PictureDraft.h"
#include "../Painter.h"
#include <boost/range/adaptor/reversed.hpp>
#include <boost/test/tools/output_test_stream.hpp>

namespace
{
class PainterInReversedOrder : public IPainter
{
public:
	void DrawPicture(const PictureDraft& draft, ICanvas& canvas) override
	{
		std::vector<const Shape*> stack;
		for (const auto& shape : draft)
		{
			stack.emplace_back(std::addressof(shape));
		}
		for (const auto& shape : boost::adaptors::reverse(stack))
		{
			shape->Draw(canvas);
		}
	}
};

class MockEllipseShape : public Shape
{
public:
	MockEllipseShape()
		: Shape(Color{0, 0, 0})
	{
	}

	void Draw(ICanvas& canvas)const override
	{
		canvas.SetColor(GetColor());
		canvas.DrawEllipse(Point2D{ 0, 0 }, 10, 10);
	}
};

class MockThreeLinedShape : public Shape
{
public:
	MockThreeLinedShape()
		: Shape(Color{0, 0, 0})
	{
	}

	void Draw(ICanvas& canvas)const override
	{
		canvas.SetColor(GetColor());
		canvas.DrawLine(Point2D{ 0, 0 }, Point2D{ 1, 1 });
		canvas.DrawLine(Point2D{ 1, 1 }, Point2D{ 1, 0 });
		canvas.DrawLine(Point2D{ 1, 0 }, Point2D{ 0, 0 });
	}
};

class MockCanvas : public ICanvas
{
public:
	MockCanvas(boost::test_tools::output_test_stream& strm)
		: m_strm(strm)
	{
	}

	void SetColor(const Color & color) override
	{
		(void)color;
	}

	void DrawLine(const Point2D & from, const Point2D & to) override
	{
		(void)from;
		(void)to;
		m_strm << "DrawLine\n";
	}

	void DrawEllipse(const Point2D & center, float horizontalRadius, float verticalRadius) override
	{
		(void)center;
		(void)horizontalRadius;
		(void)verticalRadius;
		m_strm << "DrawEllipse\n";
	}

private:
	boost::test_tools::output_test_stream& m_strm;
};
}

// Добавил префикс 'C' к имени теста для избежания ошибок от boost'а.
BOOST_AUTO_TEST_SUITE(CPainter)
	BOOST_AUTO_TEST_CASE(draws_shapes_in_strict_order)
	{
		boost::test_tools::output_test_stream strm;
		MockCanvas canvas(strm);

		PictureDraft draft;
		draft.AddShape(std::make_unique<MockEllipseShape>());
		draft.AddShape(std::make_unique<MockThreeLinedShape>());

		// Нарисует на холсте фигуры в обратном порядке
		PainterInReversedOrder reversed;
		reversed.DrawPicture(draft, canvas);
		BOOST_CHECK(strm.is_equal(
			"DrawLine\n"
			"DrawLine\n"
			"DrawLine\n"
			"DrawEllipse\n"));

		// Нарисует на холсте фигуры в обычном порядке
		Painter regular;
		regular.DrawPicture(draft, canvas);
		BOOST_CHECK(strm.is_equal(
			"DrawEllipse\n"
			"DrawLine\n"
			"DrawLine\n"
			"DrawLine\n"));
	}
BOOST_AUTO_TEST_SUITE_END()
