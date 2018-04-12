#include "stdafx.h"
#include "../InsertImageCommand.h"
#include "ImageFileStorageMock.h"
#include "DocumentControlMock.h"

namespace
{
struct InsertImageCommandFixture
{
	InsertImageCommandFixture()
		: control(strm)
		, storage(&strm)
	{
	}

	std::unique_ptr<InsertImageCommand> CreateAndExecuteCommand()
	{
		auto command = std::make_unique<InsertImageCommand>(
			100, 500, storage.AddImage("%TEMP%/image.jpg"), boost::none, storage);
		command->Execute(control);
		BOOST_CHECK(strm.is_equal("ii %TEMP%/image.jpg 100 500 end"));
		return command;
	}

	ImageFileStorageMock storage;
	DocumentCommandControlMock control;
	boost::test_tools::output_test_stream strm;
};
}

BOOST_FIXTURE_TEST_SUITE(CInsertImageCommand, InsertImageCommandFixture)
	BOOST_AUTO_TEST_CASE(image_will_be_copied_by_storage_on_execute_once_when_command_destroyed)
	{
		{
			auto command = CreateAndExecuteCommand();
		}
		storage.CopyTo("C:/Windows");
		BOOST_CHECK(strm.is_equal("%TEMP%/image.jpg copied to C:/Windows"));
	}

	BOOST_AUTO_TEST_CASE(image_will_not_be_copied_and_will_be_deleted_from_storage_if_command_is_unexecuted)
	{
		{
			auto command = CreateAndExecuteCommand();
			command->Unexecute(control);
			storage.CopyTo("C:/Windows");
			BOOST_CHECK(strm.is_equal("d end"));
		}
		//  оманда вставки была отменена и удалена, значит хранилище должно удалить ресурс
		BOOST_CHECK(strm.is_equal("Delete %TEMP%/image.jpg"));
	}

	BOOST_AUTO_TEST_CASE(image_will_be_copied_and_will_not_be_deleted_from_storage_if_command_is_executed_twice)
	{
		{
			auto command = CreateAndExecuteCommand();

			command->Unexecute(control);
			BOOST_CHECK(strm.is_equal("d end"));

			storage.CopyTo("C:/Windows");
			BOOST_CHECK(strm.is_empty());

			command->Execute(control);
			BOOST_CHECK(strm.is_equal("ii %TEMP%/image.jpg 100 500 end"));
		}
		//  оманда вставки была отменена и затем выполнена снова, после удалени€ команды хранилще
		//  ничего не должно делать
		BOOST_CHECK(strm.is_empty());

		storage.CopyTo("C:/Windows");
		BOOST_CHECK(strm.is_equal("%TEMP%/image.jpg copied to C:/Windows"));
	}
BOOST_AUTO_TEST_SUITE_END()
