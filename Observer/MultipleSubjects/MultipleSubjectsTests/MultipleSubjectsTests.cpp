#include "stdafx.h"
#include "../Observer.h"

#include <vector>
#include <string>
#include <boost/test/output_test_stream.hpp>

namespace
{
class Observable : public AbstractObservable<int>
{
public:
	void SetData(int data)
	{
		m_data = data;
		NotifyObservers();
	}

private:
	// Inherited via AbstractObservable
	virtual int GetChangedData() const override
	{
		return m_data;
	}

	int m_data = 0;
};

class Observer : public IObserver<int>
{
public:
	Observer(Observable& first, Observable& second, const std::string& name,
		boost::test_tools::output_test_stream& output)
		: m_first(first)
		, m_second(second)
		, m_name(name)
		, m_output(output)
	{
		m_first.RegisterObserver(*this);
		m_second.RegisterObserver(*this);
	}

	~Observer()
	{
		m_first.RemoveObserver(*this);
		m_second.RemoveObserver(*this);
	}

	void Update(const int& data, IObservable<int> & observable) override
	{
		if (std::addressof(observable) == std::addressof(m_first))
		{
			m_output << "[first_" << m_name << "]";
		}
		else if (std::addressof(observable) == std::addressof(m_second))
		{
			m_output << "[second_" << m_name << "]";
		}
	}

private:
	Observable & m_first;
	Observable & m_second;

	std::string m_name;
	boost::test_tools::output_test_stream& m_output;
};
}

BOOST_AUTO_TEST_SUITE(MultipleSubjects)
	BOOST_AUTO_TEST_CASE(observers_can_distinguish_subjects)
	{
		boost::test_tools::output_test_stream output;

		Observable first;
		Observable second;

		Observer observer1(first, second, "a", output);
		first.SetData(100500);
		BOOST_CHECK(output.is_equal("[first_a]", true));

		Observer observer2(first, second, "b", output);
		second.SetData(100500);
		// Не забываем, что порядок обхода наблюдателей никак не гарантирован
		BOOST_CHECK(output.is_equal("[second_a][second_b]", false) ||
			output.is_equal("[second_a][second_b]", false));

		output.flush();
		BOOST_CHECK(output.is_empty());

		Observable other;
		other.RegisterObserver(observer2);
		other.SetData(100500);
		BOOST_CHECK(output.is_empty());

		first.SetData(100500);
		BOOST_CHECK(output.is_equal("[first_a][first_b]", false) ||
			output.is_equal("[first_b][first_a]", false));
	}
BOOST_AUTO_TEST_SUITE_END()
