#include "stdafx.h"
#include "../Image.h"
#include "CommandManagerMock.h"
#include <boost/test/tools/output_test_stream.hpp>

BOOST_AUTO_TEST_SUITE(CImage)
	BOOST_AUTO_TEST_CASE(cant_be_constructed_with_not_allowed_size)
	{
		boost::test_tools::output_test_stream output;
		CommandManagerMock manager(output);

		// нижн€€ граница
		BOOST_REQUIRE_THROW(Image("path", 0u, 0u, manager), std::invalid_argument);
		BOOST_REQUIRE_THROW(Image("path", 0u, 10u, manager), std::invalid_argument);
		BOOST_REQUIRE_THROW(Image("path", 10u, 0u, manager), std::invalid_argument);

		// верхн€€ граница
		BOOST_REQUIRE_THROW(Image("path", 10001u, 10001u, manager), std::invalid_argument);
		BOOST_REQUIRE_THROW(Image("path", 10000u, 10001u, manager), std::invalid_argument);
		BOOST_REQUIRE_THROW(Image("path", 10001u, 10000u, manager), std::invalid_argument);

		// разрешЄнные размеры
		BOOST_REQUIRE_NO_THROW(Image("path", 9999u, 9999u, manager));
	}

	BOOST_AUTO_TEST_CASE(cant_be_resized_to_not_allowed_size)
	{
		boost::test_tools::output_test_stream output;
		CommandManagerMock manager(output);
		Image image("path", 9999u, 9999u, manager);

		// нижн€€ граница
		BOOST_REQUIRE_THROW(image.Resize(0u, 0u), std::invalid_argument);
		BOOST_REQUIRE_THROW(image.Resize(0u, 10u), std::invalid_argument);
		BOOST_REQUIRE_THROW(image.Resize(10u, 0u), std::invalid_argument);

		// верхн€€ граница
		BOOST_REQUIRE_THROW(image.Resize(10001u, 10001u), std::invalid_argument);
		BOOST_REQUIRE_THROW(image.Resize(10000u, 10001u), std::invalid_argument);
		BOOST_REQUIRE_THROW(image.Resize(10001u, 10000u), std::invalid_argument);
	}

	BOOST_AUTO_TEST_CASE(can_be_resized_and_then_undo_and_then_redo_that_command)
	{
		boost::test_tools::output_test_stream output;
		CommandManagerMock manager(output);

		Image image("path", 9999u, 9999u, manager);
		image.Resize(100u, 1000u);
		BOOST_CHECK(output.is_equal("Command executed"));

		BOOST_CHECK_EQUAL(image.GetWidth(), 100u);
		BOOST_CHECK_EQUAL(image.GetHeight(), 1000u);

		manager.Undo();
		BOOST_CHECK(output.is_equal("Command unexecuted"));
		BOOST_CHECK_EQUAL(image.GetWidth(), 9999u);
		BOOST_CHECK_EQUAL(image.GetHeight(), 9999u);

		manager.Redo();
		BOOST_CHECK(output.is_equal("Command reexecuted"));
		BOOST_CHECK_EQUAL(image.GetWidth(), 100u);
		BOOST_CHECK_EQUAL(image.GetHeight(), 1000u);
	}
BOOST_AUTO_TEST_SUITE_END()
