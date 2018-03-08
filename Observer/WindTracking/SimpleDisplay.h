#pragma once
#include "WeatherStation.h"

// ������� �������, ������� ���������� � ����� ������
//  ��� ��������� ����������� �� ��������� ������ �� �������� �������
class SimpleDisplay : public IObserver<WeatherEvent, WeatherInfo>
{
public:
	SimpleDisplay(InnerWeatherStation& station);
	~SimpleDisplay();

private:
	void Update(const WeatherInfo& info, const IObservable<WeatherEvent, WeatherInfo>& observable) override;

	InnerWeatherStation& m_station;
};
