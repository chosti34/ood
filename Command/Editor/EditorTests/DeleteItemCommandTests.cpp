#include "stdafx.h"
#include "../DeleteItemCommand.h"
#include "ImageFileStorageMock.h"
#include "../Paragraph.h"
#include "../Image.h"
#include "../CommandManager.h"
#include <boost/test/tools/output_test_stream.hpp>
#include <boost/optional.hpp>

namespace
{
struct DeleteItemCommandFixture
{
	DeleteItemCommandFixture()
		: storage(std::make_shared<ImageFileStorageMock>(&strm))
		, manager(10)
	{
		for (int i = 0; i < 3; ++i)
		{
			items.push_back(
				std::make_shared<DocumentItem>(
					std::make_shared<Paragraph>(std::to_string(i), manager), nullptr));
		}
	}

	std::shared_ptr<ImageFileStorageMock> storage;
	CommandManager manager;
	std::vector<std::shared_ptr<DocumentItem>> items;
	boost::test_tools::output_test_stream strm;
};
}

BOOST_FIXTURE_TEST_SUITE(CDeleteItemCommand, DeleteItemCommandFixture)
	BOOST_AUTO_TEST_CASE(can_remove_item_from_any_position)
	{
		auto command1 = std::make_unique<DeleteItemCommand>(1, items, storage);
		command1->Execute();

		BOOST_CHECK(items.size() == 2);
		BOOST_CHECK(items[0]->GetParagraph()->GetText() == "0");
		BOOST_CHECK(items[1]->GetParagraph()->GetText() == "2");

		auto command2 = std::make_unique<DeleteItemCommand>(items.size() - 1, items, storage);
		command2->Execute();

		BOOST_CHECK(items.size() == 1);
		BOOST_CHECK(items[0]->GetParagraph()->GetText() == "0");
	}

	BOOST_AUTO_TEST_CASE(inserts_item_at_old_position_on_undo)
	{
		BOOST_CHECK(items[1]->GetParagraph()->GetText() == "1");
		auto command = std::make_unique<DeleteItemCommand>(1, items, storage);
		command->Execute();
		BOOST_CHECK(items[1]->GetParagraph()->GetText() == "2");

		command->Unexecute();
		BOOST_CHECK(items.size() == 3);
		BOOST_CHECK(items[1]->GetParagraph()->GetText() == "1");
	}

	BOOST_AUTO_TEST_CASE(image_file_will_not_be_copied_and_will_be_deleted_if_command_is_executed)
	{
		{
			items.push_back(std::make_shared<DocumentItem>(
				nullptr, std::make_shared<Image>(storage->AddImage("path"), 100, 500, manager)));

			auto command = std::make_unique<DeleteItemCommand>(items.size() - 1, items, storage);
			command->Execute();
			BOOST_CHECK(items.back()->GetParagraph()->GetText() == "2");

			storage->CopyTo("C:/Windows");
			BOOST_CHECK(strm.is_empty());
		}
		BOOST_CHECK(strm.is_equal("Delete path"));
	}

	BOOST_AUTO_TEST_CASE(image_file_will_be_copied_and_will_not_be_deleted_if_command_is_undoned)
	{
		{
			items.push_back(std::make_shared<DocumentItem>(
				nullptr, std::make_shared<Image>(storage->AddImage("path"), 100, 500, manager)));

			auto command = std::make_unique<DeleteItemCommand>(items.size() - 1, items, storage);
			command->Execute();

			storage->CopyTo("C:/Windows");
			BOOST_CHECK(strm.is_empty());

			command->Unexecute();
			storage->CopyTo("C:/Windows");

			BOOST_CHECK(strm.is_equal("path copied to C:/Windows"));
		}
		BOOST_CHECK(strm.is_empty());
	}
BOOST_AUTO_TEST_SUITE_END()
