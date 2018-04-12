#include "stdafx.h"
#include "../InsertParagraphCommand.h"
#include "DocumentControlMock.h"
#include <boost/test/tools/output_test_stream.hpp>

struct InsertParagraphCommandExecutedFixture
{
	InsertParagraphCommandExecutedFixture()
		: command("paragraph text", boost::none)
		, control(strm)
		, strm()
	{
		command.Execute(control);
	}

	boost::test_tools::output_test_stream strm;
	InsertParagraphCommand command;
	DocumentCommandControlMock control;
};

BOOST_FIXTURE_TEST_SUITE(CInsertParagraphCommand, InsertParagraphCommandExecutedFixture)
	BOOST_AUTO_TEST_CASE(inserts_paragraph_at_specified_position)
	{
		BOOST_CHECK(strm.is_equal("ip paragraph text end"));
	}

	BOOST_AUTO_TEST_CASE(removes_paragraph_on_command_undoing)
	{
		strm.flush();
		command.Unexecute(control);
		BOOST_CHECK(strm.is_equal("d end"));
	}
BOOST_AUTO_TEST_SUITE_END()
