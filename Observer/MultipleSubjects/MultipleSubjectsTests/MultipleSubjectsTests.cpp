#include "stdafx.h"
#include "../WeatherData.h"
#include <vector>
#include <string>
#include <boost/test/output_test_stream.hpp>

namespace
{
class MockDisplay : public InOutSensorDisplay
{
public:
	MockDisplay(WeatherData& in, WeatherData& out,
		const std::string& name,
		boost::test_tools::output_test_stream& output)
		: InOutSensorDisplay(in, out)
		, m_name(name)
		, m_output(output)
	{
	}

	void Update(const WeatherInfo& data, IObservable<WeatherInfo> & sensor)
	{
		if (std::addressof(sensor) == std::addressof(m_inSensor))
		{
			m_output << "in_" << m_name;
		}
		else if (std::addressof(sensor) == std::addressof(m_outSensor))
		{
			m_output << "out_" << m_name;
		}
	}

private:
	std::string m_name;
	boost::test_tools::output_test_stream& m_output;
};
}

BOOST_AUTO_TEST_SUITE(MultipleSubjects)
	BOOST_AUTO_TEST_CASE(observers_can_distinguish_subjects)
	{
		boost::test_tools::output_test_stream output;

		WeatherData in;
		WeatherData out;

		MockDisplay display(in, out, "a", output);
		in.SetMeasurements(10, 0.5, 600);

		BOOST_CHECK(output.is_equal("in_a"));
		out.SetMeasurements(15, 0.6, 800);
		BOOST_CHECK(output.is_equal("out_a"));
	}
BOOST_AUTO_TEST_SUITE_END()
