#include "stdafx.h"
#include "WeatherData.h"

class NumberObservable : public AbstractObservable<int>
{
public:
	void SetData(int data)
	{
		m_data = data;
		NotifyObservers();
	}

private:
	// Inherited via AbstractObservable
	int GetChangedData() const override
	{
		return m_data;
	}

	int m_data;
};

class DumbObserver : public IObserver<int>
{
public:
	DumbObserver(AbstractObservable<int>& observable)
		: m_observable(observable)
	{
		m_observable.RegisterObserver(*this);
	}

private:
	void Update(const int& data) override
	{
		m_observable.RemoveObserver(*this);
	}

	AbstractObservable<int>& m_observable;
};

int main(int /* argc */, char* /* argv */[])
{
	WeatherData weatherData;

	SimpleDisplay simpleDisplay;
	weatherData.RegisterObserver(simpleDisplay);

	StatisticsDisplay statisticsDisplay;
	weatherData.RegisterObserver(statisticsDisplay);

	weatherData.SetMeasurements(3, 0.7, 760);
	weatherData.SetMeasurements(4, 0.8, 761);

	weatherData.RemoveObserver(statisticsDisplay);

	weatherData.SetMeasurements(10, 0.8, 761);
	weatherData.SetMeasurements(-10, 0.8, 761);

	NumberObservable o;
	DumbObserver dumb1(o);
	DumbObserver dumb2(o);
	o.SetData(1);

	return 0;
}
