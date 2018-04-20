#include "stdafx.h"
#include "../Paragraph.h"
#include "CommandManagerMock.h"
#include <boost/test/tools/output_test_stream.hpp>

BOOST_AUTO_TEST_SUITE(CParagraph)
	BOOST_AUTO_TEST_CASE(can_set_text_and_then_undo_and_then_redo_that_command)
	{
		boost::test_tools::output_test_stream output;
		CommandManagerMock manager(output);

		Paragraph paragraph("hello", manager);
		BOOST_CHECK_EQUAL(paragraph.GetText(), "hello");

		paragraph.SetText("world");
		BOOST_CHECK(output.is_equal("Command executed"));
		BOOST_CHECK_EQUAL(paragraph.GetText(), "world");

		manager.Undo();
		BOOST_CHECK(output.is_equal("Command unexecuted"));
		BOOST_CHECK_EQUAL(paragraph.GetText(), "hello");

		manager.Redo();
		BOOST_CHECK(output.is_equal("Command reexecuted"));
		BOOST_CHECK_EQUAL(paragraph.GetText(), "world");
	}
BOOST_AUTO_TEST_SUITE_END()
