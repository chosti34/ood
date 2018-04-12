#include "stdafx.h"
#include "../DocumentMenu.h"
#include "../IImageFileStorage.h"
#include "../IDocument.h"
#include "../DocumentSerializer.h"
#include "ImageFileStorageMock.h"
#include <boost/test/tools/output_test_stream.hpp>

namespace
{
class DocumentMock : public IDocument
{
public:
	DocumentMock(boost::test_tools::output_test_stream& output)
		: m_output(output)
		, m_itemsCount(0)
		, m_title("untitled")
	{
	}

	void InsertParagraph(const std::string& text, boost::optional<size_t> position) override
	{
		m_output << "InsertParagraph " << text << " at "
			<< (position ? std::to_string(*position) : "the end");
		++m_itemsCount;
	}

	void InsertImage(const std::string& path, unsigned width, unsigned height, boost::optional<size_t> position) override
	{
		m_output << "InsertImage " << path << " " << width << " " << height << " at "
			<< (position ? std::to_string(*position) : "the end");
		++m_itemsCount;
	}

	void RemoveItem(size_t index) override
	{
		m_output << "Remove item at " << index;
		--m_itemsCount;
	}

	void ReplaceText(const std::string& text, size_t index) override
	{
		m_output << "Replace text at " << index << " to " << text;
	}

	void ResizeImage(unsigned width, unsigned height, size_t index) override
	{
		m_output << "Resize image at " << index << " to " << width << " " << height;
	}

	size_t GetItemsCount() const override
	{
		return m_itemsCount;
	}

	std::shared_ptr<DocumentItem> GetItem(size_t) override
	{
		return nullptr;
	}

	std::shared_ptr<const DocumentItem> GetItem(size_t) const override
	{
		return nullptr;
	}

	void SetTitle(const std::string& title) override
	{
		m_title = title;
	}

	std::string GetTitle() const override
	{
		return m_title;
	}

	bool CanUndo() const override
	{
		return true;
	}

	void Undo() override
	{
		m_output << "Undo";
	}

	bool CanRedo() const override
	{
		return true;
	}

	void Redo() override
	{
		m_output << "Redo";
	}

private:
	std::string m_title;
	boost::test_tools::output_test_stream& m_output;
	size_t m_itemsCount;
};

struct DocumentMenuFixture
{
	DocumentMenuFixture()
		: document(strm)
		, menu(document, storage, strm)
	{
	}

	boost::test_tools::output_test_stream strm;
	DocumentMenu menu;
	ImageFileStorageMock storage;
	DocumentMock document;
};
}

BOOST_FIXTURE_TEST_SUITE(CDocumentMenu, DocumentMenuFixture)
	BOOST_AUTO_TEST_CASE(does_nothing_when_input_command_is_not_recognized)
	{
		BOOST_CHECK(!menu.ExecuteCommand(""));
		BOOST_CHECK(!menu.ExecuteCommand("DoCommand 1 1 1"));
		BOOST_CHECK(!menu.ExecuteCommand("SetTitl abcd"));
		BOOST_CHECK(strm.is_equal("Unknown command!\nUnknown command!\nUnknown command!\n"));
	}

	BOOST_AUTO_TEST_SUITE(invoke_document_method_when_input_is_recognized)
		BOOST_AUTO_TEST_CASE(insert_paragraph_method)
		{
			BOOST_CHECK(menu.ExecuteCommand("InsertParagraph end abcd"));
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1u);
			BOOST_CHECK(strm.is_equal("InsertParagraph abcd at the end"));
			BOOST_CHECK(menu.ExecuteCommand("InsertParagraph end 123"));
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 2u);
			BOOST_CHECK(strm.is_equal("InsertParagraph 123 at the end"));
		}

		BOOST_AUTO_TEST_CASE(insert_image_method)
		{
			BOOST_CHECK(menu.ExecuteCommand("InsertImage end 100 200 path"));
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 1u);
			BOOST_CHECK(strm.is_equal("InsertImage path 100 200 at the end"));
		}

		BOOST_AUTO_TEST_CASE(remove_item_method)
		{
			BOOST_CHECK(menu.ExecuteCommand("InsertParagraph end abcd"));
			BOOST_CHECK(strm.is_equal("InsertParagraph abcd at the end"));
			BOOST_CHECK(menu.ExecuteCommand("DeleteItem 0"));
			BOOST_CHECK(strm.is_equal("Remove item at 0"));
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0u);
		}

		BOOST_AUTO_TEST_CASE(replace_text_method)
		{
			BOOST_CHECK(menu.ExecuteCommand("ReplaceText 123 newtext"));
			BOOST_CHECK(strm.is_equal("Replace text at 123 to newtext"));
		}

		BOOST_AUTO_TEST_CASE(resize_image_method)
		{
			BOOST_CHECK(menu.ExecuteCommand("ResizeImage 0 100 200"));
			BOOST_CHECK(strm.is_equal("Resize image at 0 to 100 200"));
		}

		BOOST_AUTO_TEST_CASE(set_title_method)
		{
			BOOST_CHECK(document.GetTitle() == "untitled");
			BOOST_CHECK(menu.ExecuteCommand("SetTitle abcd"));
			BOOST_CHECK(document.GetTitle() == "abcd");
		}

		BOOST_AUTO_TEST_CASE(undo_method)
		{
			BOOST_CHECK(menu.ExecuteCommand("Undo"));
			BOOST_CHECK(strm.is_equal("Undo"));
		}

		BOOST_AUTO_TEST_CASE(redo_method)
		{
			BOOST_CHECK(menu.ExecuteCommand("Redo"));
			BOOST_CHECK(strm.is_equal("Redo"));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(document_method_is_not_invoked_when_arguments_are_wrong)
		BOOST_AUTO_TEST_CASE(insert_paragraph_method)
		{
			// Вставляем в начало через неверный индекс
			BOOST_REQUIRE_THROW(menu.ExecuteCommand("InsertParagraph a12 abcd"), std::invalid_argument);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0u);

			// Аргументов меньше чем надо
			menu.ExecuteCommand("InsertParagraph 0");
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0u);

			// Аргументов больше чем надо
			menu.ExecuteCommand("InsertParagraph end abcd 123");
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0u);
		}

		BOOST_AUTO_TEST_CASE(insert_image_method)
		{
			// Вставляем через неверный индекс
			BOOST_REQUIRE_THROW(menu.ExecuteCommand("InsertImage index 100 200 path"), std::invalid_argument);
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0u);

			// Аргументов меньше чем надо
			menu.ExecuteCommand("InsertImage 1 2 3");
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0u);

			// Аргументов больше чем надо
			menu.ExecuteCommand("InsertImage end 100 200 path 123");
			BOOST_CHECK_EQUAL(document.GetItemsCount(), 0u);
		}

		BOOST_AUTO_TEST_CASE(remove_item_method)
		{
			// Пытаемся удалить через неверный индекс
			BOOST_REQUIRE_THROW(menu.ExecuteCommand("DeleteItem x"), std::invalid_argument);

			// Аргументов меньше чем надо
			menu.ExecuteCommand("DeleteItem");
			BOOST_CHECK(strm.is_equal("Expected 1 arguments, 0 given\n"));

			// Аргументов больше чем надо
			menu.ExecuteCommand("DeleteItem 0 1");
			BOOST_CHECK(strm.is_equal("Expected 1 arguments, 2 given\n"));
		}

		BOOST_AUTO_TEST_CASE(replace_text_method)
		{
			// Пытаемся изменить текст используя неправильный индекс
			BOOST_REQUIRE_THROW(menu.ExecuteCommand("ReplaceText abcd NewText"), std::invalid_argument);

			// Аргументов меньше чем надо
			menu.ExecuteCommand("ReplaceText 0");
			BOOST_CHECK(strm.is_equal("Expected 2 arguments, 1 given\n"));

			// Аргументов больше чем надо
			menu.ExecuteCommand("ReplaceText 0 text 123");
			BOOST_CHECK(strm.is_equal("Expected 2 arguments, 3 given\n"));
		}

		BOOST_AUTO_TEST_CASE(resize_image_method)
		{
			// Пытаемся изменить размеры используя неправильный индекс
			BOOST_REQUIRE_THROW(menu.ExecuteCommand("ResizeImage abcd 100 500"), std::invalid_argument);

			// Аргументов меньше чем надо
			menu.ExecuteCommand("ResizeImage 0 100");
			BOOST_CHECK(strm.is_equal("Expected 3 arguments, 2 given\n"));

			// Аргументов больше чем надо
			menu.ExecuteCommand("ResizeImage 0 100 500 123");
			BOOST_CHECK(strm.is_equal("Expected 3 arguments, 4 given\n"));
		}

		BOOST_AUTO_TEST_CASE(set_title_method)
		{
			// Без аргументов
			menu.ExecuteCommand("SetTitle");
			BOOST_CHECK(strm.is_equal("Expected 1 arguments, 0 given\n"));

			// Аргументов больше чем надо
			menu.ExecuteCommand("SetTitle 123 AnotherArgument");
			BOOST_CHECK(strm.is_equal("Expected 1 arguments, 2 given\n"));
		}

		BOOST_AUTO_TEST_CASE(undo_method)
		{
			// Аргументов больше чем надо
			menu.ExecuteCommand("Undo AdditionalArgument");
			BOOST_CHECK(strm.is_equal("Expected 0 arguments, 1 given\n"));
		}

		BOOST_AUTO_TEST_CASE(redo_method)
		{
			// Аргументов больше чем надо
			menu.ExecuteCommand("Redo AdditionalArgument");
			BOOST_CHECK(strm.is_equal("Expected 0 arguments, 1 given\n"));
		}
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
