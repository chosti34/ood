#include "stdafx.h"
#include "../WeatherData.h"
#include <vector>
#include <string>
#include <boost/test/output_test_stream.hpp>

namespace
{
class AdvancedDisplay : public IObserver<WeatherInfo>
{
public:
	AdvancedDisplay(WeatherData& innerStation, WeatherData& outerStation, const std::string& name,
		boost::test_tools::output_test_stream& output)
		: m_innerStation(innerStation)
		, m_outerStation(outerStation)
		, m_name(name)
		, m_output(output)
	{
		m_innerStation.RegisterObserver(*this);
		m_outerStation.RegisterObserver(*this);
	}

	~AdvancedDisplay()
	{
		m_innerStation.RemoveObserver(*this);
		m_outerStation.RemoveObserver(*this);
	}

	void Update(const WeatherInfo& data, IObservable<WeatherInfo> & sensor) override
	{
		if (std::addressof(sensor) == std::addressof(m_innerStation))
		{
			m_output << "[in_" << m_name << "]";
		}
		else if (std::addressof(sensor) == std::addressof(m_outerStation))
		{
			m_output << "[out_" << m_name << "]";
		}
	}

private:
	WeatherData & m_innerStation;
	WeatherData & m_outerStation;

	std::string m_name;
	boost::test_tools::output_test_stream& m_output;
};
}

BOOST_AUTO_TEST_SUITE(MultipleSubjects)
	BOOST_AUTO_TEST_CASE(observers_can_distinguish_subjects)
	{
		boost::test_tools::output_test_stream output;

		WeatherData innerStation;
		WeatherData outerStation;

		AdvancedDisplay display1(innerStation, outerStation, "a", output);
		innerStation.SetMeasurements(10, 0.5, 600);
		BOOST_CHECK(output.is_equal("[in_a]", true));

		AdvancedDisplay display2(innerStation, outerStation, "b", output);
		outerStation.SetMeasurements(15, 0.6, 800);
		// Не забываем, что порядок обхода наблюдателей никак не гарантирован
		BOOST_CHECK(output.is_equal("[out_a][out_b]", false) || output.is_equal("[out_a][out_b]", false));

		output.flush();
		BOOST_CHECK(output.is_empty());

		WeatherData otherStation;
		otherStation.RegisterObserver(display2);
		otherStation.SetMeasurements(15, 0.5, 500);
		BOOST_CHECK(output.is_empty());

		innerStation.SetMeasurements(20, 0.8, 700);
		BOOST_CHECK(output.is_equal("[in_a][in_b]", false) || output.is_equal("[in_b][in_a]", false));
	}
BOOST_AUTO_TEST_SUITE_END()
