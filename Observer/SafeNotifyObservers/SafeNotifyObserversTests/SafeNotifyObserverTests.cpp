#include "stdafx.h"
#include "../Observer.h"
#include <boost/test/output_test_stream.hpp>

namespace
{
class DummyObservable : public AbstractObservable<int>
{
public:
	void SetData(int data)
	{
		m_data = data;
		NotifyObservers();
	}

private:
	virtual int GetChangedData() const override
	{
		return m_data;
	}

	int m_data;
};

class DummyObserver : public IObserver<int>
{
public:
	DummyObserver(DummyObservable& observable, const std::string& name,
		bool eraseOnUpdate,
		boost::test_tools::output_test_stream& output)
		: m_observable(observable)
		, m_name(name)
		, m_eraseOnUpdate(eraseOnUpdate)
		, m_output(output)
	{
		m_observable.RegisterObserver(*this);
	}

	~DummyObserver()
	{
		// Не должно вызвать падение программы
		m_observable.RemoveObserver(*this);
	}

	void Update(const int& data) override
	{
		m_output << m_name;
		if (m_eraseOnUpdate)
		{
			// Не должно вызвать падение программы
			m_observable.RemoveObserver(*this);
		}
	}

	void SetEraseOnUpdate(bool eraseOnUpdate)
	{
		m_eraseOnUpdate = eraseOnUpdate;
	}

private:
	DummyObservable& m_observable;
	boost::test_tools::output_test_stream& m_output;
	std::string m_name;
	bool m_eraseOnUpdate;
};
}

BOOST_AUTO_TEST_SUITE(WeatherStation)
	BOOST_AUTO_TEST_CASE(subsribers_can_remove_themselves_from_list_safely)
	{
		boost::test_tools::output_test_stream output;

		DummyObservable observable;
		DummyObserver observer1(observable, "a", true, output);
		DummyObserver observer2(observable, "b", false, output);

		observable.SetData(123);
		// Не забываем что порядок обхода наблюдателей никак не гарантирован
		BOOST_CHECK(output.is_equal("ab", false) || output.is_equal("ba", false));

		output.flush();
		BOOST_CHECK(output.is_empty());

		observer2.SetEraseOnUpdate(true);
		observable.SetData(456);
		// Наблюдатель с именем "a" удалил себя из подписчиков в прошлом уведомлении
		BOOST_CHECK(output.is_equal("b"));

		output.flush();
		BOOST_CHECK(output.is_empty());

		// Наблюдатель с именем "b" удалил себя из подписчиков в прошлом уведомлении
		observable.SetData(789);
		BOOST_CHECK(output.is_empty());
	}
BOOST_AUTO_TEST_SUITE_END()
