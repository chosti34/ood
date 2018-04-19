#include "stdafx.h"
#include "../app/adapters.h"
#include "../shape_drawing_lib/Rectangle.h"
#include "../shape_drawing_lib/Triangle.h"
#include <iostream>
#include <boost/test/tools/output_test_stream.hpp>

// Тесты для адаптера объектов
BOOST_AUTO_TEST_SUITE(object_adapter)
	BOOST_AUTO_TEST_CASE(calls_begin_draw_method_when_created)
	{
		boost::test_tools::output_test_stream output;
		modern_graphics_lib::CModernGraphicsRenderer renderer(output);
		ModernGraphicsRendererObjectAdapter adapter(renderer);
		BOOST_CHECK(output.is_equal("<draw>\n"));
	}

	BOOST_AUTO_TEST_CASE(calls_end_draw_method_when_adaptee_object_destroyed)
	{
		boost::test_tools::output_test_stream output;
		{
			modern_graphics_lib::CModernGraphicsRenderer renderer(output);
			ModernGraphicsRendererObjectAdapter adapter(renderer);
		}
		BOOST_CHECK(output.is_equal("<draw>\n</draw>\n"));
	}

	BOOST_AUTO_TEST_CASE(moves_pen_into_line_ending_point_after_drawing_a_line)
	{
		boost::test_tools::output_test_stream output;
		modern_graphics_lib::CModernGraphicsRenderer renderer(output);
		ModernGraphicsRendererObjectAdapter adapter(renderer);
		BOOST_CHECK(output.is_equal("<draw>\n"));

		adapter.MoveTo(0, 0);
		adapter.LineTo(10, 10);
		BOOST_CHECK(output.is_equal(
			"  <line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"10\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"));

		adapter.LineTo(20, 20);
		BOOST_CHECK(output.is_equal(
			"  <line fromX=\"10\" fromY=\"10\" toX=\"20\" toY=\"20\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"));
	}

	BOOST_AUTO_TEST_CASE(moves_pen_after_drawing_new_shape)
	{
		boost::test_tools::output_test_stream output;
		modern_graphics_lib::CModernGraphicsRenderer renderer(output);
		ModernGraphicsRendererObjectAdapter adapter(renderer);
		BOOST_CHECK(output.is_equal("<draw>\n"));

		shape_drawing_lib::CRectangle rectangle({ 0, 0 }, 10, 10);
		shape_drawing_lib::CTriangle triangle({ 1, 1 }, { 3, 3 }, { 2, 1 });

		rectangle.Draw(adapter);
		BOOST_CHECK(output.is_equal(
			"  <line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"0\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"10\" fromY=\"0\" toX=\"10\" toY=\"10\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"10\" fromY=\"10\" toX=\"0\" toY=\"10\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"0\" fromY=\"10\" toX=\"0\" toY=\"0\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"));

		triangle.Draw(adapter);
		BOOST_CHECK(output.is_equal(
			"  <line fromX=\"1\" fromY=\"1\" toX=\"3\" toY=\"3\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"3\" fromY=\"3\" toX=\"2\" toY=\"1\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"2\" fromY=\"1\" toX=\"1\" toY=\"1\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"));
	}

	BOOST_AUTO_TEST_CASE(changes_color_when_drawing_new_shape)
	{
		boost::test_tools::output_test_stream output;
		modern_graphics_lib::CModernGraphicsRenderer renderer(output);
		ModernGraphicsRendererObjectAdapter adapter(renderer);
		BOOST_CHECK(output.is_equal("<draw>\n"));

		adapter.SetColor(0x0000ff); // синий цвет
		adapter.MoveTo(0, 0);
		adapter.LineTo(10, 10);

		BOOST_CHECK(output.is_equal(
			"  <line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"10\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"1\" a=\"1\" />\n"
			"  </line>\n"));

		shape_drawing_lib::CTriangle triangle({ 0, 0 }, { 1, 1 }, { 0, 2 }, 0xff0000);
		triangle.Draw(adapter);

		// цвет поменялся
		BOOST_CHECK(output.is_equal(
			"  <line fromX=\"0\" fromY=\"0\" toX=\"1\" toY=\"1\" />\n"
			"    <color r=\"1\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"1\" fromY=\"1\" toX=\"0\" toY=\"2\" />\n"
			"    <color r=\"1\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"0\" fromY=\"2\" toX=\"0\" toY=\"0\" />\n"
			"    <color r=\"1\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"));
	}
BOOST_AUTO_TEST_SUITE_END()

// Тесты для адаптера классов
BOOST_AUTO_TEST_SUITE(class_adapter)
	BOOST_AUTO_TEST_CASE(calls_begin_draw_method_when_created)
	{
		boost::test_tools::output_test_stream output;
		ModernGraphicsRendererClassAdapter adapter(output);
		BOOST_CHECK(output.is_equal("<draw>\n"));
	}

	BOOST_AUTO_TEST_CASE(calls_end_draw_method_when_adaptee_object_destroyed)
	{
		boost::test_tools::output_test_stream output;
		{
			ModernGraphicsRendererClassAdapter adapter(output);
		}
		BOOST_CHECK(output.is_equal("<draw>\n</draw>\n"));
	}

	BOOST_AUTO_TEST_CASE(moves_pen_into_ending_point_when_drawing_a_line)
	{
		boost::test_tools::output_test_stream output;
		ModernGraphicsRendererClassAdapter adapter(output);
		BOOST_CHECK(output.is_equal("<draw>\n"));

		adapter.MoveTo(0, 0);
		adapter.LineTo(10, 10);
		BOOST_CHECK(output.is_equal(
			"  <line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"10\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"));

		adapter.LineTo(20, 20);
		BOOST_CHECK(output.is_equal(
			"  <line fromX=\"10\" fromY=\"10\" toX=\"20\" toY=\"20\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"));
	}

	BOOST_AUTO_TEST_CASE(moves_pen_after_drawing_new_shape)
	{
		boost::test_tools::output_test_stream output;
		ModernGraphicsRendererClassAdapter adapter(output);
		BOOST_CHECK(output.is_equal("<draw>\n"));

		shape_drawing_lib::CRectangle rectangle({ 0, 0 }, 10, 10);
		shape_drawing_lib::CTriangle triangle({ 1, 1 }, { 3, 3 }, { 2, 1 });

		rectangle.Draw(adapter);
		BOOST_CHECK(output.is_equal(
			"  <line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"0\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"10\" fromY=\"0\" toX=\"10\" toY=\"10\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"10\" fromY=\"10\" toX=\"0\" toY=\"10\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"0\" fromY=\"10\" toX=\"0\" toY=\"0\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"));

		triangle.Draw(adapter);
		BOOST_CHECK(output.is_equal(
			"  <line fromX=\"1\" fromY=\"1\" toX=\"3\" toY=\"3\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"3\" fromY=\"3\" toX=\"2\" toY=\"1\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"2\" fromY=\"1\" toX=\"1\" toY=\"1\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"));
	}

	BOOST_AUTO_TEST_CASE(changes_color_when_drawing_new_shape)
	{
		boost::test_tools::output_test_stream output;
		ModernGraphicsRendererClassAdapter adapter(output);
		BOOST_CHECK(output.is_equal("<draw>\n"));

		adapter.SetColor(0x0000ff); // синий цвет
		adapter.MoveTo(0, 0);
		adapter.LineTo(10, 10);

		BOOST_CHECK(output.is_equal(
			"  <line fromX=\"0\" fromY=\"0\" toX=\"10\" toY=\"10\" />\n"
			"    <color r=\"0\" g=\"0\" b=\"1\" a=\"1\" />\n"
			"  </line>\n"));

		shape_drawing_lib::CTriangle triangle({ 0, 0 }, { 1, 1 }, { 0, 2 }, 0xff0000);
		triangle.Draw(adapter);

		// цвет поменялся
		BOOST_CHECK(output.is_equal(
			"  <line fromX=\"0\" fromY=\"0\" toX=\"1\" toY=\"1\" />\n"
			"    <color r=\"1\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"1\" fromY=\"1\" toX=\"0\" toY=\"2\" />\n"
			"    <color r=\"1\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"
			"  <line fromX=\"0\" fromY=\"2\" toX=\"0\" toY=\"0\" />\n"
			"    <color r=\"1\" g=\"0\" b=\"0\" a=\"1\" />\n"
			"  </line>\n"));
	}
BOOST_AUTO_TEST_SUITE_END()
