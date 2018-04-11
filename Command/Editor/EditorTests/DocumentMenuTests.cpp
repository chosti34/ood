#include "stdafx.h"
#include "../DocumentMenu.h"
#include "../ImageFileStorage.h"
#include "../Document.h"

//class DocumentMock : public IDocument
//{
//public:
//	void InsertParagraph(const std::string & text, boost::optional<size_t> position) override
//	{
//	}
//	void InsertImage(const std::string & path, unsigned width, unsigned height, boost::optional<size_t> position) override
//	{
//	}
//	void RemoveItem(size_t index) override
//	{
//	}
//	void ReplaceText(const std::string & text, size_t index) override
//	{
//	}
//	void ResizeImage(unsigned width, unsigned height, size_t index) override
//	{
//	}
//	size_t GetItemsCount() const override
//	{
//		return size_t();
//	}
//	std::shared_ptr<DocumentItem> GetItem(size_t index) override
//	{
//		return std::shared_ptr<DocumentItem>();
//	}
//	std::shared_ptr<const DocumentItem> GetItem(size_t index) const override
//	{
//		return std::shared_ptr<const DocumentItem>();
//	}
//	void SetTitle(const std::string & title) override
//	{
//	}
//	std::string GetTitle() const override
//	{
//		return std::string();
//	}
//	bool CanUndo() const override
//	{
//		return false;
//	}
//	void Undo() override
//	{
//	}
//	bool CanRedo() const override
//	{
//		return false;
//	}
//	void Redo() override
//	{
//	}
//};

struct DocumentMenuFixture
{
	DocumentMenuFixture()
		: document(storage)
		, menu(document, storage)
	{
	}

	DocumentMenu menu;
	ImageFileStorage storage;
	Document document;
};

BOOST_FIXTURE_TEST_SUITE(CDocumentMenu, DocumentMenuFixture)
	BOOST_AUTO_TEST_CASE(can_dispatch_input_commands)
	{
		//menu.ExecuteCommand("");
	}
BOOST_AUTO_TEST_SUITE_END()
