#include "stdafx.h"
#include "../Color.h"
#include "../CompositeShape.h"
#include "../IOutlineStyle.h"
#include "../IFillStyle.h"
#include "../Ellipse.h"
#include "../Rectangle.h"
#include "../Triangle.h"

namespace
{
bool FramesAreEqual(const RectF& lhs, const RectF& rhs)
{
	return lhs.left == rhs.left && lhs.top == rhs.top &&
		lhs.width == rhs.width && lhs.height == rhs.height;
}

void RequireDefaultChildrenStyleValues(const CompositeShape& composite)
{
	for (size_t i = 0; i < composite.GetShapesCount(); ++i)
	{
		BOOST_REQUIRE_EQUAL(*composite.GetShape(i)->GetFillStyle().IsEnabled(), true);
		BOOST_REQUIRE_EQUAL(*composite.GetShape(i)->GetFillStyle().GetColor(), MapRGB(0xff, 0xff, 0xff));
		BOOST_REQUIRE_EQUAL(*composite.GetShape(i)->GetOutlineStyle().IsEnabled(), true);
		BOOST_REQUIRE_EQUAL(*composite.GetShape(i)->GetOutlineStyle().GetColor(), MapRGB(0xff, 0xff, 0xff));
		BOOST_REQUIRE_EQUAL(*composite.GetShape(i)->GetOutlineStyle().GetThickness(), 1.f);
	}
}
}

BOOST_AUTO_TEST_SUITE(CCompositeShape)
	struct CompositeShapeFixture
	{
		CompositeShape composite;
	};

	BOOST_FIXTURE_TEST_SUITE(when_created, CompositeShapeFixture)
		BOOST_AUTO_TEST_CASE(has_no_children)
		{
			BOOST_CHECK_EQUAL(composite.GetShapesCount(), 0);
		}

		BOOST_AUTO_TEST_CASE(throws_exception_when_trying_to_get_frame)
		{
			BOOST_CHECK_THROW(composite.GetFrame(), std::logic_error);
		}

		BOOST_AUTO_TEST_CASE(throws_exception_when_trying_to_set_frame)
		{
			BOOST_CHECK_THROW(composite.SetFrame(RectF{ 0, 0, 10, 10 }), std::logic_error);
		}

		BOOST_AUTO_TEST_CASE(fill_and_outline_styles_properties_has_boost_none_values)
		{
			BOOST_CHECK(composite.GetFillStyle().IsEnabled() == boost::none);
			BOOST_CHECK(composite.GetFillStyle().GetColor() == boost::none);
			BOOST_CHECK(composite.GetOutlineStyle().IsEnabled() == boost::none);
			BOOST_CHECK(composite.GetOutlineStyle().GetColor() == boost::none);
			BOOST_CHECK(composite.GetOutlineStyle().GetThickness() == boost::none);
		}
	BOOST_AUTO_TEST_SUITE_END()

	struct CompositeShapeWithShapesFixture : CompositeShapeFixture
	{
		CompositeShapeWithShapesFixture()
		{
			composite.InsertShape(std::make_shared<shapelib::Ellipse>(Point2D{ 0, 0 }, 10.f, 10.f));
			composite.InsertShape(std::make_shared<shapelib::Rectangle>(Point2D{ 10, 10 }, 15.f, 15.f));
			composite.InsertShape(std::make_shared<shapelib::Triangle>(Point2D{ 0, 0 }, Point2D{ 1, 1 }, Point2D{0, 3}));

			auto innerComposite = std::make_shared<CompositeShape>();
			innerComposite->InsertShape(std::make_shared<shapelib::Rectangle>(Point2D{ 5, 5 }, 5.f, 5.f));

			composite.InsertShape(innerComposite);
		}
	};

	BOOST_FIXTURE_TEST_SUITE(when_has_some_shapes, CompositeShapeWithShapesFixture)
		BOOST_AUTO_TEST_CASE(get_frame_method_returns_common_bounding_rect_for_all_shapes)
		{
			auto frame = composite.GetFrame();
			BOOST_CHECK(FramesAreEqual(frame, RectF{-10.f, -10.f, 35.f, 35.f}));
		}

		BOOST_AUTO_TEST_CASE(set_frame_method_resize_all_shapes_proportionally)
		{
			// Смещаем составную фигуру на 10 единиц вправо и вниз
			composite.SetFrame(RectF{ 0, 0, 35.f, 35.f });
			BOOST_CHECK(FramesAreEqual(composite.GetShape(0)->GetFrame(), RectF{ 0.f, 0.f, 20.f, 20.f }));
			BOOST_CHECK(FramesAreEqual(composite.GetShape(1)->GetFrame(), RectF{ 20.f, 20.f, 15.f, 15.f }));
			BOOST_CHECK(FramesAreEqual(composite.GetShape(2)->GetFrame(), RectF{ 10, 10, 1, 3 }));
			BOOST_CHECK(FramesAreEqual(composite.GetShape(3)->GetFrame(), RectF{ 15, 15, 5, 5 }));
		}

		BOOST_AUTO_TEST_CASE(changing_fill_style_affects_every_child_shape)
		{
			RequireDefaultChildrenStyleValues(composite);

			// Ставим первой фигуре другой цвет заливки
			composite.GetShape(0)->GetFillStyle().SetColor(MapRGB(0x00, 0x00, 0x00));
			BOOST_REQUIRE(composite.GetFillStyle().GetColor() == boost::none);

			// Устанавливаем всей составной фигуре новый цвет
			composite.GetFillStyle().SetColor(MapRGB(0xff, 0x00, 0xff));

			// Проверяем, что всем дочерним элементам был установлен новый цвет заливки
			for (size_t i = 0; i < composite.GetShapesCount(); ++i)
			{
				BOOST_CHECK(composite.GetShape(i)->GetFillStyle().GetColor() == MapRGB(0xff, 0x00, 0xff));
			}
		}

		BOOST_AUTO_TEST_CASE(changing_outline_style_affects_every_child_shape)
		{
			RequireDefaultChildrenStyleValues(composite);

			// Устанавливаем первой фигуре другую толщину и цвет обводки
			composite.GetShape(0)->GetOutlineStyle().SetColor(MapRGB(0x00, 0x00, 0x00));
			composite.GetShape(0)->GetOutlineStyle().SetThickness(2.f);
			BOOST_REQUIRE(composite.GetOutlineStyle().GetColor() == boost::none);
			BOOST_REQUIRE(composite.GetOutlineStyle().GetThickness() == boost::none);

			// Устанавливаем составной фигуре новый цвет и толщину обводки
			composite.GetOutlineStyle().SetColor(MapRGB(0xff, 0x00, 0xff));
			composite.GetOutlineStyle().SetThickness(1.f);

			// Проверяем, что всем дочерним элементам был установлен новая толщина и цвет обводки
			for (size_t i = 0; i < composite.GetShapesCount(); ++i)
			{
				BOOST_CHECK(composite.GetShape(i)->GetOutlineStyle().GetColor() == MapRGB(0xff, 0x00, 0xff));
				BOOST_CHECK(composite.GetShape(i)->GetOutlineStyle().GetThickness() == 1.f);
			}
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(get_composite_method_returns_pointer_to_itself)
	{
		CompositeShape shape;
		BOOST_CHECK_EQUAL(shape.GetComposite(), &shape);
	}
BOOST_AUTO_TEST_SUITE_END()
