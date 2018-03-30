#include "stdafx.h"
#include "../ShapeFactory.h"
#include "../Ellipse.h"
#include "../Rectangle.h"
#include "../Triangle.h"
#include "../RegularPolygon.h"
#include "../Point2D.h"
#include <string>

namespace
{
struct ShapeFactoryFixture
{
	ShapeFactory factory;
};
}

// Добавил префикс 'C' к имени теста для избежания ошибок от boost'а.
BOOST_FIXTURE_TEST_SUITE(CShapeFactory, ShapeFactoryFixture)
	BOOST_AUTO_TEST_CASE(throws_exception_on_unknown_shape_name)
	{
		const std::vector<std::string> failureCommands = {
			"krug 100500", "cubik 1 1 1", "kvadrat 3"
		};
		for (const auto& failureCommand : failureCommands)
		{
			BOOST_REQUIRE_THROW(factory.CreateShape(failureCommand), std::invalid_argument);
		}
	}

	BOOST_AUTO_TEST_CASE(can_create_ellipse)
	{
		auto shape = factory.CreateShape("Ellipse 0 0 10 10 red");
		BOOST_CHECK(typeid(*shape) == typeid(Ellipse));
		Ellipse* ellipse = dynamic_cast<Ellipse*>(shape.get());
		BOOST_REQUIRE(ellipse != nullptr);

		Point2D expectedCenter{ 0, 0 };
		Color expectedColor{ 255, 0, 0 };
		BOOST_CHECK_EQUAL(ellipse->GetHorizontalRadius(), 10);
		BOOST_CHECK_EQUAL(ellipse->GetVerticalRadius(), 10);
		BOOST_CHECK(ellipse->GetCenter() == expectedCenter);
		BOOST_CHECK(ellipse->GetColor() == expectedColor);
	}

	BOOST_AUTO_TEST_CASE(can_create_rectangle)
	{
		auto shape = factory.CreateShape("Rectangle 0 0 10 10 red");
		BOOST_CHECK(typeid(*shape) == typeid(Rectangle));
		Rectangle* rectangle = dynamic_cast<Rectangle*>(shape.get());
		BOOST_REQUIRE(rectangle != nullptr);

		Point2D expectedLeftTop{ 0, 0 };
		Point2D expectedRightBottom{ 10, 10 };
		Color expectedColor{ 255, 0, 0 };
		BOOST_CHECK(rectangle->GetLeftTop() == expectedLeftTop);
		BOOST_CHECK(rectangle->GetRightBottom() == expectedRightBottom);
		BOOST_CHECK(rectangle->GetColor() == expectedColor);
	}

	BOOST_AUTO_TEST_CASE(can_create_triangle)
	{
		auto shape = factory.CreateShape("Triangle 0 0 10 10 20 0 green");
		BOOST_CHECK(typeid(*shape) == typeid(Triangle));
		Triangle* triangle = dynamic_cast<Triangle*>(shape.get());
		BOOST_REQUIRE(triangle != nullptr);

		Point2D expectedVertex1{ 0, 0 };
		Point2D expectedVertex2{ 10, 10 };
		Point2D expectedVertex3{ 20, 0 };
		Color expectedColor{ 0, 255, 0 };
		BOOST_CHECK(triangle->GetVertex1() == expectedVertex1);
		BOOST_CHECK(triangle->GetVertex2() == expectedVertex2);
		BOOST_CHECK(triangle->GetVertex3() == expectedVertex3);
		BOOST_CHECK(triangle->GetColor() == expectedColor);
	}

	BOOST_AUTO_TEST_CASE(can_create_regular_polygon)
	{
		auto shape = factory.CreateShape("RegularPolygon 0 0 100 3 blue");
		BOOST_CHECK(typeid(*shape) == typeid(RegularPolygon));
		RegularPolygon* polygon = dynamic_cast<RegularPolygon*>(shape.get());
		BOOST_REQUIRE(polygon != nullptr);

		Point2D expectedCenter{ 0, 0 };
		Color expectedColor{ 0, 0, 255 };
		BOOST_CHECK_EQUAL(polygon->GetRadius(), 100.f);
		BOOST_CHECK_EQUAL(polygon->GetVertexCount(), 3u);
		BOOST_CHECK(polygon->GetCenter() == expectedCenter);
		BOOST_CHECK(polygon->GetColor() == expectedColor);
	}
BOOST_AUTO_TEST_SUITE_END()
