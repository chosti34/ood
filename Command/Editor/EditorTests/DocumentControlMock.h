#pragma once
#include "../IDocumentCommandControl.h"
#include "../Image.h"
#include <boost/test/tools/output_test_stream.hpp>

class DocumentCommandControlMock : public IDocumentCommandControl
{
public:
	DocumentCommandControlMock(boost::test_tools::output_test_stream& strm)
		: m_strm(strm)
	{
	}

	virtual void DoInsertItem(
		const std::shared_ptr<DocumentItem>& item, boost::optional<size_t> position) override
	{
		if (item->GetParagraph())
		{
			BOOST_CHECK(!item->GetImage());
			m_strm << "ip " << item->GetParagraph()->GetText()
				<< " " << (position ? std::to_string(*position) : "end");
		}
		if (item->GetImage())
		{
			BOOST_CHECK(!item->GetParagraph());
			m_strm << "ii " << item->GetImage()->GetPath() << " " << item->GetImage()->GetWidth()
				<< " " << item->GetImage()->GetHeight() << " " << (position ? std::to_string(*position) : "end");
		}
		if (!item->GetImage() && !item->GetParagraph())
		{
			m_strm << "iu " << (position ? std::to_string(*position) : "end");
		}
	}

	std::shared_ptr<DocumentItem> DoRemoveItem(boost::optional<size_t> position) override
	{
		m_strm << "d " << (position ? std::to_string(*position) : "end");

		// Всегда возвращает картинку, для удобства тестирования
		return std::make_shared<DocumentItem>(nullptr, std::make_shared<Image>("path", 100, 500));
	}

	void DoSetTitle(const std::string&) override
	{
	}

	void DoReplaceText(const std::string&, size_t) override
	{
	}

	void DoResizeImage(unsigned, unsigned, size_t) override
	{
	}

private:
	boost::test_tools::output_test_stream& m_strm;
};
