#include "stdafx.h"
#include "../Designer.h"
#include "../Shape.h"
#include "../Color.h"
#include "../PictureDraft.h"

#include <boost/range/algorithm/copy.hpp>
#include <boost/algorithm/cxx11/all_of.hpp>

using namespace std;

namespace
{
class MockShape : public Shape
{
public:
	MockShape(const std::string& description)
		: Shape({ 0, 0, 0 })
		, description(description)
	{
	}

	void Draw(ICanvas& canvas)const override
	{
		(void)canvas;
	}

	std::string description;
};

struct MockShapeFactory : IShapeFactory
{
	vector<string> shapeDescriptions;
	// Inherited via IShapeFactory
	unique_ptr<Shape> CreateShape(const std::string& description) override
	{
		// Запротоколировали описание созданной фигуры
		shapeDescriptions.push_back(description);
		return make_unique<MockShape>(description);
	}
};

struct Designer_
{
	Designer_()
		: factory()
		, designer(factory)
	{
	}

	MockShapeFactory factory;
	Designer designer;
};
}

// boost ругается на совпадение имён класса Designer и набора тестов
//  поэтому я добавил префикс 'C' к имени набора тестов
BOOST_FIXTURE_TEST_SUITE(CDesigner, Designer_)
	BOOST_AUTO_TEST_SUITE(when_creating_draft)
		BOOST_AUTO_TEST_CASE(returns_empty_draft_when_input_is_empty)
		{
			istringstream input;
			auto draft = designer.CreateDraft(input);
			BOOST_CHECK(draft.IsEmpty());
			BOOST_CHECK(input.eof());
		}

		struct when_creating_draft_with_non_empty_input_ : Designer_
		{
			vector<string> expectedDescriptions = { "square", "circle", "triangle" };
			stringstream strm;
			PictureDraft draft;

			when_creating_draft_with_non_empty_input_()
			{
				boost::copy(expectedDescriptions, ostream_iterator<string>(strm, "\n"));
				draft = designer.CreateDraft(strm);
			}
		};

		BOOST_FIXTURE_TEST_SUITE(when_creating_draft_with_non_empty_input, when_creating_draft_with_non_empty_input_)
			BOOST_AUTO_TEST_CASE(passes_each_line_from_input_to_shape_factory)
			{
				BOOST_CHECK(factory.shapeDescriptions == expectedDescriptions);
			}
			BOOST_AUTO_TEST_CASE(returns_draft_with_shapes_created_by_factory)
			{
				vector<string> shapeDescriptions;
				transform(draft.begin(), draft.end(), back_inserter(shapeDescriptions), [](auto& shape) {
					auto shapeAsMockShape = dynamic_cast<const MockShape*>(&shape);
					BOOST_REQUIRE(shapeAsMockShape);
					return shapeAsMockShape->description;
				});
				// BOOST_CHECK(shapeDescriptions == expectedDescriptions);
			}
		BOOST_AUTO_TEST_SUITE_END()
	BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
