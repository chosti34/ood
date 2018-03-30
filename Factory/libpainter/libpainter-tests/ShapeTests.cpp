#pragma once
#include "stdafx.h"
#include "../Shape.h"
#include "../Ellipse.h"
#include "../Rectangle.h"
#include "../Triangle.h"
#include "../RegularPolygon.h"
#include <boost/test/tools/output_test_stream.hpp>
#include <stdexcept>
#include <vector>
#include <array>

namespace
{
class MockShape : public Shape
{
public:
	MockShape(const Color& color)
		: Shape(color)
	{
	}

	void Draw(ICanvas& canvas)const override
	{
		canvas.SetColor(GetColor());
		canvas.DrawEllipse(Point2D{ 0, 0 }, 10, 20);
		canvas.DrawLine(Point2D{ 0, 0 }, Point2D{ 1, 1 });
	}
};

class MockCanvas : public ICanvas
{
public:
	MockCanvas(boost::test_tools::output_test_stream& strm, bool verbose = false)
		: m_strm(strm)
		, m_verbose(verbose)
	{
	}

	void SetColor(const Color & color) override
	{
		m_strm << "SetColor" << (m_verbose ? " " + ToString(color) : "") << "\n";
	}

	void DrawLine(const Point2D & from, const Point2D & to) override
	{
		m_strm << "DrawLine";
		if (m_verbose)
		{
			m_strm << " (" << from.x << ", " << from.y << ") - ("
				<< to.x << ", " << to.y << ")";
		}
		m_strm << "\n";
	}

	void DrawEllipse(const Point2D & center, float horizontalRadius, float verticalRadius) override
	{
		m_strm << "DrawEllipse";
		if (m_verbose)
		{
			m_strm << " (" << center.x << ", " << center.y << ") - "
				<< horizontalRadius << " - " << verticalRadius;
		}
		m_strm << "\n";
	}

private:
	boost::test_tools::output_test_stream& m_strm;
	bool m_verbose;
};
}

// Добавил префикс 'C' к имени теста для избежания ошибок от boost'а.
BOOST_AUTO_TEST_SUITE(CShape)
	BOOST_AUTO_TEST_CASE(has_color)
	{
		Color expected{ 0xff, 0x12, 0x0f };
		MockShape shape(expected);
		Color actual = shape.GetColor();
		BOOST_CHECK_EQUAL(actual.r, expected.r);
		BOOST_CHECK_EQUAL(actual.g, expected.g);
		BOOST_CHECK_EQUAL(actual.b, expected.b);
	}

	BOOST_AUTO_TEST_CASE(can_be_drawn_on_canvas)
	{
		MockShape shape(Color{ 0, 0, 0 });
		boost::test_tools::output_test_stream strm;
		MockCanvas canvas(strm);
		shape.Draw(canvas);
		BOOST_CHECK(strm.is_equal("SetColor\nDrawEllipse\nDrawLine\n"));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CEllipse)
	BOOST_AUTO_TEST_CASE(cant_be_constructed_with_negative_or_zero_radius)
	{
		BOOST_REQUIRE_THROW(Ellipse({ 0, 0 }, -10, 10, Color{ 0, 0, 0 }), std::invalid_argument);
		BOOST_REQUIRE_THROW(Ellipse({ 0, 0 }, 5, -10, Color{ 0, 0, 0 }), std::invalid_argument);
		BOOST_REQUIRE_THROW(Ellipse({ 0, 0 }, 0, 10, Color{ 0, 0, 0 }), std::invalid_argument);
		BOOST_REQUIRE_NO_THROW(Ellipse({ 0, 0 }, 10, 10, Color{ 0, 0, 0 }));
	}

	BOOST_AUTO_TEST_CASE(can_be_drawn_on_canvas_via_draw_ellipse_method_only)
	{
		boost::test_tools::output_test_stream strm;
		const Color color{ 255, 255, 0 };
		const Point2D center{ 0, 0 };
		const float horizontal = 10;
		const float vertical = 20;
		Ellipse ellipse(center, horizontal, vertical, color);
		MockCanvas canvas(strm, true);
		ellipse.Draw(canvas);
		BOOST_CHECK(strm.is_equal("SetColor ffff00\nDrawEllipse (0, 0) - 10 - 20\n"));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CRectangle)
	BOOST_AUTO_TEST_CASE(cant_be_constructed_with_incorrect_points_location)
	{
		const std::vector<std::pair<Point2D, Point2D>> pairs = {
			{ Point2D{10, 10}, Point2D{10, 10} }, // same points
			{ Point2D{10, 10}, Point2D{10, 20} }, // same line
			{ Point2D{10, 10}, Point2D{5, 0} } // right bottom point is actually top left
		};

		for (const auto& pair : pairs)
		{
			const auto& leftTop = pair.first;
			const auto& rightBottom = pair.second;
			BOOST_REQUIRE_THROW(Rectangle(leftTop, rightBottom, Color{0, 0, 0}), std::invalid_argument);
		}
	}

	BOOST_AUTO_TEST_CASE(can_be_drawn_on_canvas_via_four_draw_line_method_calls)
	{
		boost::test_tools::output_test_stream strm;
		const Color color{ 100, 255, 10 };
		const Point2D leftTop{ 100, 100 };
		const Point2D rightBottom{ 200, 300 };
		Rectangle rectangle(leftTop, rightBottom, color);
		MockCanvas canvas(strm, true);
		rectangle.Draw(canvas);
		BOOST_CHECK(strm.is_equal(
			"SetColor 64ff0a\n"
			"DrawLine (100, 100) - (200, 100)\n"
			"DrawLine (200, 100) - (200, 300)\n"
			"DrawLine (200, 300) - (100, 300)\n"
			"DrawLine (100, 300) - (100, 100)\n"));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CTriangle)
	BOOST_AUTO_TEST_CASE(cant_be_constructed_with_incorrect_points_location)
	{
		const std::vector<std::array<Point2D, 3>> tuples = {
			{ Point2D{ 10, 10 }, Point2D{ 10, 10 }, Point2D{ 10, 10 } }, // same points
			{ Point2D{ 10, 10 }, Point2D{ 15, 15 }, Point2D{ 20, 20 } }, // same line
		};

		for (const auto& tuple : tuples)
		{
			BOOST_REQUIRE_THROW(
				Triangle(tuple[0], tuple[1], tuple[2], Color{ 0, 0, 0 }), std::invalid_argument);
		}
	}

	BOOST_AUTO_TEST_CASE(can_be_drawn_on_canvas_via_three_draw_line_method_calls)
	{
		boost::test_tools::output_test_stream strm;
		const Color color{ 0, 11, 15 };
		const Point2D p1{ 100, 100 };
		const Point2D p2{ 100, 300 };
		const Point2D p3{ 300, 100 };
		Triangle triangle(p1, p2, p3, color);
		MockCanvas canvas(strm, true);
		triangle.Draw(canvas);
		BOOST_CHECK(strm.is_equal(
			"SetColor 000b0f\n"
			"DrawLine (100, 100) - (100, 300)\n"
			"DrawLine (100, 300) - (300, 100)\n"
			"DrawLine (300, 100) - (100, 100)\n"));
	}
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(CRegularPolygon)
	BOOST_AUTO_TEST_CASE(cant_be_constructed_with_negative_or_zero_radius_and_vertex_count_less_than_three)
	{
		BOOST_REQUIRE_THROW(RegularPolygon({ 0, 0 }, -1, 3, Color{ 0, 0, 0 }), std::invalid_argument);
		BOOST_REQUIRE_THROW(RegularPolygon({ 0, 0 }, 0, 3, Color{ 0, 0, 0 }), std::invalid_argument);
		BOOST_REQUIRE_THROW(RegularPolygon({ 0, 0 }, 40, 0, Color{ 0, 0, 0 }), std::invalid_argument);
		BOOST_REQUIRE_THROW(RegularPolygon({ 0, 0 }, 40, 1, Color{ 0, 0, 0 }), std::invalid_argument);
		BOOST_REQUIRE_THROW(RegularPolygon({ 0, 0 }, 40, 2, Color{ 0, 0, 0 }), std::invalid_argument);
		BOOST_REQUIRE_NO_THROW(RegularPolygon({ 0, 0 }, 40, 3, Color{ 0, 0, 0 }));
	}

	BOOST_AUTO_TEST_CASE(canvas_draw_line_method_calls_count_depends_on_shape_vertex_count)
	{
		boost::test_tools::output_test_stream strm;
		MockCanvas canvas(strm);

		for (unsigned count = 3u; count < 32u; ++count)
		{
			RegularPolygon polygon({ 0, 0 }, 10, count, Color{0, 0, 0});
			polygon.Draw(canvas);
			std::string expected("SetColor\n");
			for (unsigned i = 0; i < count; ++i)
			{
				expected.append("DrawLine\n");
			}
			BOOST_CHECK(strm.is_equal(expected));
		}
	}
BOOST_AUTO_TEST_SUITE_END()
