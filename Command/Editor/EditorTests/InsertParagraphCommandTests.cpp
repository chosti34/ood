#include "stdafx.h"
#include "../InsertParagraphCommand.h"
#include "../CommandManager.h"
#include <boost/test/tools/output_test_stream.hpp>
#include "../Paragraph.h"
#include <boost/optional.hpp>

namespace
{
struct InsertParagraphCommandFixture
{
	InsertParagraphCommandFixture()
		: manager(10)
		, command1(boost::none, std::make_shared<Paragraph>("Text", manager), items)
		, command2(0, std::make_shared<Paragraph>("Hello", manager), items)
	{
	}

	std::vector<std::shared_ptr<DocumentItem>> items;
	CommandManager manager;

	InsertParagraphCommand command1;
	InsertParagraphCommand command2;
};
}

BOOST_FIXTURE_TEST_SUITE(CInsertParagraphCommand, InsertParagraphCommandFixture)
	BOOST_AUTO_TEST_CASE(inserts_paragraph_at_specified_position)
	{
		command1.Execute();
		BOOST_CHECK_EQUAL(items.size(), 1u);
		BOOST_CHECK(items.front()->GetParagraph()->GetText() == "Text");

		command2.Execute();
		BOOST_CHECK_EQUAL(items.size(), 2u);
		BOOST_CHECK(items.front()->GetParagraph()->GetText() == "Hello");
	}

	BOOST_AUTO_TEST_CASE(removes_paragraph_on_command_undoing)
	{
		command1.Execute();
		command2.Execute();

		command2.Unexecute();
		BOOST_CHECK_EQUAL(items.size(), 1u);
		BOOST_CHECK(items.front()->GetParagraph()->GetText() == "Text");

		command1.Unexecute();
		BOOST_CHECK(items.empty());
	}
BOOST_AUTO_TEST_SUITE_END()
