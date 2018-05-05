#include "stdafx.h"
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
}

BOOST_AUTO_TEST_SUITE(CCompositeShape)
	BOOST_AUTO_TEST_CASE(throws_exception_when_trying_to_get_frame_from_empty_composite)
	{
		CompositeShape composite;
		BOOST_CHECK_THROW(composite.GetFrame(), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(throws_exception_when_trying_to_set_frame_to_empty_composite)
	{
		CompositeShape composite;
		BOOST_CHECK_THROW(composite.SetFrame(RectF{ 0, 0, 10, 10 }), std::logic_error);
	}

	struct CompositeShapeFixture
	{
		CompositeShapeFixture()
		{
			composite.InsertShape(std::make_shared<shapelib::Ellipse>(Point2D{ 0, 0 }, 10.f, 10.f));
			composite.InsertShape(std::make_shared<shapelib::Rectangle>(Point2D{ 10, 10 }, 15.f, 15.f));
			composite.InsertShape(std::make_shared<shapelib::Triangle>(Point2D{ 0, 0 }, Point2D{ 1, 1 }, Point2D{0, 3}));
		}

		CompositeShape composite;
	};

	BOOST_FIXTURE_TEST_SUITE(when_has_some_shapes, CompositeShapeFixture)
		BOOST_AUTO_TEST_CASE(get_frame_method_returns_common_bounding_rect_for_all_shapes)
		{
			auto frame = composite.GetFrame();
			BOOST_CHECK(FramesAreEqual(frame, RectF{-10.f, -10.f, 35.f, 35.f}));
		}

		BOOST_AUTO_TEST_CASE(set_frame_method_resize_all_shapes_proportionally)
		{
			composite.SetFrame(RectF{ 0, 0, 35.f, 35.f });
			BOOST_CHECK(FramesAreEqual(composite.GetShape(0)->GetFrame(), RectF{ 0.f, 0.f, 20.f, 20.f }));
			BOOST_CHECK(FramesAreEqual(composite.GetShape(1)->GetFrame(), RectF{ 20.f, 20.f, 15.f, 15.f }));
			BOOST_CHECK(FramesAreEqual(composite.GetShape(2)->GetFrame(), RectF{ 10, 10, 1, 3 }));
		}

		BOOST_AUTO_TEST_CASE(changing_fill_style_affects_every_child_shape)
		{
			composite.GetShape(0)->GetFillStyle().SetColor(0x000000ff);
			BOOST_REQUIRE(composite.GetFillStyle().GetColor() == boost::none);

			composite.GetFillStyle().SetColor(0xff00ff00);
			for (size_t i = 0; i < composite.GetShapesCount(); ++i)
			{
				BOOST_CHECK(composite.GetShape(i)->GetFillStyle().GetColor() == 0xff00ff00);
			}
		}

		BOOST_AUTO_TEST_CASE(changing_outline_style_affects_every_child_shape)
		{
			composite.GetShape(0)->GetOutlineStyle().SetColor(0x000000ff);
			composite.GetShape(0)->GetOutlineStyle().SetThickness(2.f);
			BOOST_REQUIRE(composite.GetOutlineStyle().GetColor() == boost::none);
			BOOST_REQUIRE(composite.GetOutlineStyle().GetThickness() == boost::none);

			composite.GetOutlineStyle().SetColor(0xff00ff00);
			composite.GetOutlineStyle().SetThickness(1.f);
			for (size_t i = 0; i < composite.GetShapesCount(); ++i)
			{
				BOOST_CHECK(composite.GetShape(i)->GetOutlineStyle().GetColor() == 0xff00ff00);
				BOOST_CHECK(composite.GetShape(i)->GetOutlineStyle().GetThickness() == 1.f);
			}
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
