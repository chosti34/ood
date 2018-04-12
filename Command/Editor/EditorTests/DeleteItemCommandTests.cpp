#include "stdafx.h"
#include "../DeleteItemCommand.h"
#include "ImageFileStorageMock.h"
#include "DocumentControlMock.h"

namespace
{
struct DeleteItemCommandFixture
{
	DeleteItemCommandFixture()
		: storage(&strm)
		, control(strm)
	{
	}

	std::unique_ptr<DeleteItemCommand> CreateCommand(boost::optional<size_t> index)
	{
		return std::make_unique<DeleteItemCommand>(index, storage);
	}

	ImageFileStorageMock storage;
	DocumentCommandControlMock control;
	boost::test_tools::output_test_stream strm;
};
}

BOOST_FIXTURE_TEST_SUITE(CDeleteItemCommand, DeleteItemCommandFixture)
	BOOST_AUTO_TEST_SUITE(can_remove_item)
		BOOST_AUTO_TEST_CASE(from_any_position)
		{
			auto command = CreateCommand(12);
			command->Execute(control);
			BOOST_CHECK(strm.is_equal("d 12"));
		}

		BOOST_AUTO_TEST_CASE(from_the_end)
		{
			// ��������������, ��� � ��������� ������ ���� �������
			// (��� ��������� ������� ���� �� �����)
			auto command = CreateCommand(boost::none);
			command->Execute(control);
			BOOST_CHECK(strm.is_equal("d end"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(inserts_item_at_old_position_on_undo)
	{
		auto command = CreateCommand(100500);
		command->Execute(control);
		BOOST_CHECK(strm.is_equal("d 100500"));

		// DocumentCommandControlMock ���������� ������ �������� ��� ��������
		command->Unexecute(control);
		BOOST_CHECK(strm.is_equal("ii path 100 500 100500"));
	}

	BOOST_AUTO_TEST_CASE(image_file_will_not_be_copied_and_will_be_deleted_if_command_is_executed)
	{
		{
			auto command = CreateCommand(0);
			command->Execute(control);
			BOOST_CHECK(strm.is_equal("d 0"));

			// �������� ����������� �������� ���������, ���� �� ������� ���� ������� ��������
			storage.CopyTo("C:/Windows");
			BOOST_CHECK(strm.is_empty());
		}
		BOOST_CHECK(strm.is_equal("Delete path"));
	}

	BOOST_AUTO_TEST_CASE(image_file_will_be_copied_and_will_not_be_deleted_if_command_is_undoned)
	{
		{
			// ����� ����������� ������� �������� ���������� � ���������
			storage.AddImage("path");

			auto command = CreateCommand(0);
			command->Execute(control);
			BOOST_CHECK(strm.is_equal("d 0"));

			// �������� ����������� �������� ���������, ���� �� ������� ���� ������� ��������
			storage.CopyTo("C:/Windows");
			BOOST_CHECK(strm.is_empty());

			command->Unexecute(control);
			BOOST_CHECK(strm.is_equal("ii path 100 500 0"));

			// �������� ����������� �������� ���������, ���� �� ������� ���� ������� � �������������
			storage.CopyTo("C:/Windows");
			BOOST_CHECK(strm.is_equal("path copied to C:/Windows"));
		}

		// ����� ������������ ������� �������� ��� ���� ��������, �� ���� �������� �� ���������
		//  � ���� � ��������� �� ������ ���� �����
		BOOST_CHECK(strm.is_empty());
	}
BOOST_AUTO_TEST_SUITE_END()
