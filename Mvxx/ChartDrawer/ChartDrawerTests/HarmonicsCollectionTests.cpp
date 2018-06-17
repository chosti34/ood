#include "stdafx.h"
#include "../HarmonicsCollection.h"
#include <boost/test/tools/output_test_stream.hpp>

namespace
{
bool operator ==(const Harmonic& left, const Harmonic& right)
{
	return left.GetAmplitude() == right.GetAmplitude() &&
		left.GetFrequency() == right.GetFrequency() &&
		left.GetPhase() == right.GetPhase() &&
		left.GetType() == right.GetType();
}

struct HarmonicsCollectionFixture
{
	void Fill(unsigned count)
	{
		for (unsigned i = 0; i < count; ++i)
		{
			Harmonic harmonic;
			harmonics.InsertHarmonic(harmonic);
			BOOST_REQUIRE(harmonics.GetHarmonic(i) == harmonic);
		}
		BOOST_REQUIRE(harmonics.GetCount() == count);
	}

	HarmonicsCollection harmonics;
};

class HarmonicsObserver
{
public:
	HarmonicsObserver(int label, boost::test_tools::output_test_stream& output, HarmonicsCollection& harmonics)
		: m_output(output)
		, m_label(label)
	{
		m_connections.emplace_back(harmonics.DoOnHarmonicInsertion([this]() {
			m_output << m_label << ". Harmonic inserted" << std::endl;
		}));
		m_connections.emplace_back(harmonics.DoOnHarmonicDeletion([this]() {
			m_output << m_label << ". Harmonic deleted" << std::endl;
		}));
		m_connections.emplace_back(harmonics.DoOnHarmonicPropertiesChange([this](size_t) {
			m_output << m_label << ". Harmonic changed" << std::endl;
		}));
	}

private:
	std::vector<SignalScopedConnection> m_connections;
	boost::test_tools::output_test_stream& m_output;
	int m_label;
};
}

BOOST_FIXTURE_TEST_SUITE(CHarmonicsCollection, HarmonicsCollectionFixture)
	BOOST_AUTO_TEST_SUITE(throws_exception_when)
		BOOST_AUTO_TEST_CASE(trying_to_calculate_value_of_empty_collection)
		{
			BOOST_CHECK_THROW(harmonics.CalculateValue(0), std::logic_error);
		}

		BOOST_AUTO_TEST_CASE(trying_to_delete_from_empty_collection)
		{
			BOOST_CHECK_THROW(harmonics.DeleteHarmonic(0), std::out_of_range);
		}

		BOOST_AUTO_TEST_CASE(when_providing_invalid_indices_to_set_and_get_harmonic_methods)
		{
			Harmonic harmonic;
			harmonics.InsertHarmonic(harmonic);

			BOOST_CHECK_THROW(harmonics.GetHarmonic(1), std::out_of_range);
			BOOST_CHECK_THROW(harmonics.SetHarmonic(harmonic, 1), std::out_of_range);
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(count_is_zero_by_default)
	{
		BOOST_CHECK_EQUAL(harmonics.GetCount(), 0);
	}

	BOOST_AUTO_TEST_SUITE(harmonic_can_be_inserted_at)
		BOOST_AUTO_TEST_CASE(specified_position)
		{
			Fill(1);
			harmonics.InsertHarmonic(Harmonic(1, 2, 3, HarmonicType::Cos), 0);
			BOOST_CHECK(harmonics.GetCount() == 2);
			BOOST_CHECK(harmonics.GetHarmonic(0) == Harmonic(1, 2, 3, HarmonicType::Cos));
		}

		BOOST_AUTO_TEST_CASE(the_end_when_index_is_more_or_equal_to_collection_size)
		{
			Fill(1);
			harmonics.InsertHarmonic(Harmonic(1, 2, 3, HarmonicType::Cos), 3);
			BOOST_CHECK(harmonics.GetCount() == 2);
			BOOST_CHECK(harmonics.GetHarmonic(1) == Harmonic(1, 2, 3, HarmonicType::Cos));
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_SUITE(harmonic_can_be_deleted_from)
		BOOST_AUTO_TEST_CASE(specified_position)
		{
			Fill(1);
			harmonics.DeleteHarmonic(0);
			BOOST_CHECK(harmonics.GetCount() == 0);
		}

		BOOST_AUTO_TEST_CASE(the_end_when_index_is_more_or_equal_to_collection_size)
		{
			Fill(3);
			harmonics.DeleteHarmonic(10);
			BOOST_CHECK(harmonics.GetCount() == 2);
			BOOST_CHECK(harmonics.GetHarmonic(1) == Harmonic());
		}
	BOOST_AUTO_TEST_SUITE_END()

	BOOST_AUTO_TEST_CASE(observers_can_subscribe_to_collection_notifications_and_receive_them)
	{
		Fill(3);
		boost::test_tools::output_test_stream output;
		HarmonicsObserver observer1(1, output, harmonics);
		HarmonicsObserver observer2(2, output, harmonics);

		harmonics.SetHarmonic(Harmonic(1, 2, 3, HarmonicType::Cos), 0);
		BOOST_CHECK( // порядок не определён
			output.is_equal("1. Harmonic changed\n2. Harmonic changed\n", false) ||
			output.is_equal("2. Harmonic changed\n1. Harmonic changed\n", false));

		output.flush();
		BOOST_REQUIRE(output.is_empty());

		harmonics.InsertHarmonic(Harmonic());
		BOOST_CHECK( // порядок не определён
			output.is_equal("1. Harmonic inserted\n2. Harmonic inserted\n", false) ||
			output.is_equal("2. Harmonic inserted\n1. Harmonic inserted\n", true));

		output.flush();
		BOOST_REQUIRE(output.is_empty());

		harmonics.DeleteHarmonic();
		BOOST_CHECK( // порядок не определён
			output.is_equal("1. Harmonic deleted\n2. Harmonic deleted\n", false) ||
			output.is_equal("2. Harmonic deleted\n1. Harmonic deleted\n", true));
	}

	BOOST_AUTO_TEST_CASE(observers_can_unsubscribe)
	{
		Fill(3);
		boost::test_tools::output_test_stream output;
		HarmonicsObserver observer1(1, output, harmonics);

		{
			HarmonicsObserver observer2(2, output, harmonics);

			harmonics.SetHarmonic(Harmonic(1, 2, 3, HarmonicType::Cos), 0);
			BOOST_CHECK( // порядок не определён
				output.is_equal("1. Harmonic changed\n2. Harmonic changed\n", false) ||
				output.is_equal("2. Harmonic changed\n1. Harmonic changed\n", false));

			output.flush();
			BOOST_REQUIRE(output.is_empty());
		}

		harmonics.InsertHarmonic(Harmonic());
		BOOST_CHECK(output.is_equal("1. Harmonic inserted\n", true));
		BOOST_REQUIRE(output.is_empty());

		harmonics.DeleteHarmonic();
		BOOST_CHECK(output.is_equal("1. Harmonic deleted\n", true));
	}
BOOST_AUTO_TEST_SUITE_END()
