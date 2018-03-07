#pragma once
#include "WeatherStation.h"

// ������� �������, ������� ���������� � ����� ������
//  ��� ��������� ����������� �� ��������� ������ �� �������� �������
class SimpleDisplay : public IObserver<WeatherInfo>
{
public:
	SimpleDisplay(InnerWeatherStation& station);
	~SimpleDisplay();

private:
	void Update(const WeatherInfo& info, const IObservable<WeatherInfo>& observable) override;

	InnerWeatherStation& m_station;
};
