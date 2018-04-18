#include "stdafx.h"
#include "../InsertImageCommand.h"
#include "ImageFileStorageMock.h"
#include "../Image.h"
#include "../CommandManager.h"
#include <boost/test/tools/output_test_stream.hpp>

namespace
{
struct InsertImageCommandFixture
{
	InsertImageCommandFixture()
		: storage(std::make_shared<ImageFileStorageMock>(&strm))
		, manager(10)
	{
	}

	std::unique_ptr<InsertImageCommand> CreateAndExecuteCommand()
	{
		auto image = std::make_shared<Image>(storage->AddImage("%TEMP%/image.jpg"), 100, 500, manager);
		auto command = std::make_unique<InsertImageCommand>(boost::none, image, items, storage);
		command->Execute();
		return command;
	}

	std::shared_ptr<ImageFileStorageMock> storage;
	CommandManager manager;
	std::vector<std::shared_ptr<DocumentItem>> items;
	boost::test_tools::output_test_stream strm;
};
}

BOOST_FIXTURE_TEST_SUITE(CInsertImageCommand, InsertImageCommandFixture)
	BOOST_AUTO_TEST_CASE(image_will_be_copied_by_storage_on_execute_once_when_command_destroyed)
	{
		{
			auto command = CreateAndExecuteCommand();
		}
		storage->CopyTo("C:/Windows");
		BOOST_CHECK(strm.is_equal("%TEMP%/image.jpg copied to C:/Windows"));
	}

	BOOST_AUTO_TEST_CASE(image_will_not_be_copied_and_will_be_deleted_from_storage_if_command_is_unexecuted)
	{
		{
			auto command = CreateAndExecuteCommand();
			command->Unexecute();
			storage->CopyTo("C:/Windows");
		}
		BOOST_CHECK(strm.is_equal("Delete %TEMP%/image.jpg"));
	}

	BOOST_AUTO_TEST_CASE(image_will_be_copied_and_will_not_be_deleted_from_storage_if_command_is_executed_twice)
	{
		{
			auto command = CreateAndExecuteCommand();
			command->Unexecute();

			storage->CopyTo("C:/Windows");
			BOOST_CHECK(strm.is_empty());

			command->Execute();
		}
		BOOST_CHECK(strm.is_empty());

		storage->CopyTo("C:/Windows");
		BOOST_CHECK(strm.is_equal("%TEMP%/image.jpg copied to C:/Windows"));
	}
BOOST_AUTO_TEST_SUITE_END()
