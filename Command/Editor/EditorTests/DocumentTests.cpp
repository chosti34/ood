#include "stdafx.h"
#include "../Document.h"
#include "ImageFileStorageMock.h"
#include <boost/test/tools/output_test_stream.hpp>

namespace
{
struct DocumentFixture
{
	DocumentFixture()
		: storage()
		, document(storage)
	{
	}

	Document document;
	ImageFileStorageMock storage;
};
}

BOOST_FIXTURE_TEST_SUITE(CDocument, DocumentFixture)
	BOOST_AUTO_TEST_SUITE(when_created_)
		BOOST_AUTO_TEST_CASE(has_default_title_as_untitled_string)
		{
			BOOST_CHECK_EQUAL(document.GetTitle(), "untitled");
		}

		BOOST_AUTO_TEST_CASE(has_zero_items)
		{
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0u);
		}

		BOOST_AUTO_TEST_CASE(cant_redo_and_cant_undo_anything)
		{
			BOOST_CHECK(!document.CanRedo() && !document.CanUndo());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_insert_paragraph)
		BOOST_AUTO_TEST_CASE(at_the_end_of_the_items_list)
		{
			document.InsertParagraph("SuperParagraph1", boost::none);
			document.InsertParagraph("SuperParagraph2", boost::none);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2u);
			BOOST_CHECK_EQUAL(document.GetItem(0u)->GetParagraph()->GetText(), "SuperParagraph1");
			BOOST_CHECK_EQUAL(document.GetItem(1u)->GetParagraph()->GetText(), "SuperParagraph2");
		}

		BOOST_AUTO_TEST_CASE(at_any_position)
		{
			document.InsertParagraph("SuperParagraph1", boost::none);
			document.InsertParagraph("SuperParagraph2", 0);
			document.InsertParagraph("SuperParagraph3", 1);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 3u);
			BOOST_CHECK_EQUAL(document.GetItem(0u)->GetParagraph()->GetText(), "SuperParagraph2");
			BOOST_CHECK_EQUAL(document.GetItem(1u)->GetParagraph()->GetText(), "SuperParagraph3");
			BOOST_CHECK_EQUAL(document.GetItem(2u)->GetParagraph()->GetText(), "SuperParagraph1");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_insert_image)
		BOOST_AUTO_TEST_CASE(at_the_end_of_the_items_list)
		{
			document.InsertImage("some-random-path.png", 100, 500, boost::none);
			document.InsertImage("some-random-path-2.png", 500, 100, boost::none);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2u);

			BOOST_CHECK(!document.GetItem(0u)->GetParagraph());
			BOOST_CHECK(!document.GetItem(1u)->GetParagraph());

			const auto image1 = document.GetItem(0u)->GetImage();
			const auto image2 = document.GetItem(1u)->GetImage();

			BOOST_CHECK_EQUAL(image1->GetWidth(), 100);
			BOOST_CHECK_EQUAL(image1->GetHeight(), 500);
			BOOST_CHECK_EQUAL(image1->GetPath(), "some-random-path.png");

			BOOST_CHECK_EQUAL(image2->GetWidth(), 500);
			BOOST_CHECK_EQUAL(image2->GetHeight(), 100);
			BOOST_CHECK_EQUAL(image2->GetPath(), "some-random-path-2.png");
		}

		BOOST_AUTO_TEST_CASE(at_any_position)
		{
			document.InsertImage("some-random-path.png", 100, 500, boost::none);
			document.InsertImage("some-random-path-2.png", 500, 100, 0);
			document.InsertImage("some-random-path-3.png", 1000, 100, 1);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 3u);

			BOOST_CHECK(!document.GetItem(0u)->GetParagraph());
			BOOST_CHECK(!document.GetItem(1u)->GetParagraph());
			BOOST_CHECK(!document.GetItem(2u)->GetParagraph());

			const auto image1 = document.GetItem(2u)->GetImage();
			const auto image2 = document.GetItem(0u)->GetImage();
			const auto image3 = document.GetItem(1u)->GetImage();

			BOOST_CHECK_EQUAL(image1->GetWidth(), 100);
			BOOST_CHECK_EQUAL(image1->GetHeight(), 500);
			BOOST_CHECK_EQUAL(image1->GetPath(), "some-random-path.png");

			BOOST_CHECK_EQUAL(image2->GetWidth(), 500);
			BOOST_CHECK_EQUAL(image2->GetHeight(), 100);
			BOOST_CHECK_EQUAL(image2->GetPath(), "some-random-path-2.png");

			BOOST_CHECK_EQUAL(image3->GetWidth(), 1000);
			BOOST_CHECK_EQUAL(image3->GetHeight(), 100);
			BOOST_CHECK_EQUAL(image3->GetPath(), "some-random-path-3.png");
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(can_do_and_then_undo_and_then_redo)
		BOOST_AUTO_TEST_CASE(remove_item_command)
		{
			document.InsertImage("some-random-path.png", 100, 500, boost::none);
			document.InsertParagraph("SuperParagraph1", boost::none);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2u);

			document.RemoveItem(1u);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1u);
			BOOST_CHECK(document.GetItem(0)->GetImage());

			document.RemoveItem(0u);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0u);

			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1u);
			BOOST_CHECK(document.GetItem(0)->GetImage());

			document.Undo();

			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2u);
			BOOST_CHECK(document.GetItem(0)->GetImage());
			BOOST_CHECK(document.GetItem(1)->GetParagraph());

			document.Redo();
			document.Redo();
			BOOST_CHECK(!document.CanRedo());
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0u);
		}

		BOOST_AUTO_TEST_CASE(set_title_command)
		{
			document.SetTitle("NewTitle");
			BOOST_CHECK_EQUAL(document.GetTitle(), "NewTitle");

			document.Undo();
			BOOST_CHECK_EQUAL(document.GetTitle(), "untitled");
			BOOST_CHECK(!document.CanUndo());

			document.Redo();
			BOOST_CHECK(!document.CanRedo());
			BOOST_CHECK_EQUAL(document.GetTitle(), "NewTitle");
		}

		BOOST_AUTO_TEST_CASE(insert_paragraph_command)
		{
			document.InsertParagraph("123", boost::none);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1u);

			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0u);
			BOOST_CHECK(!document.CanUndo());

			document.Redo();
			BOOST_CHECK(!document.CanRedo());
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1u);
		}

		BOOST_AUTO_TEST_CASE(insert_image_command)
		{
			document.InsertImage("path", 100, 500, boost::none);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1u);

			document.Undo();
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0u);
			BOOST_CHECK(!document.CanUndo());

			document.Redo();
			BOOST_CHECK(!document.CanRedo());
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1u);
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
