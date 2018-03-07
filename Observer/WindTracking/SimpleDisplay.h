#pragma once
#include "WeatherStation.h"

// Обычный дисплей, выводит показатели в поток вывода
//  при получении уведомления об изменении данных на погодной станции
class SimpleDisplay : public IObserver<WeatherInfo>
{
public:
	SimpleDisplay(InnerWeatherStation& station);
	~SimpleDisplay();

private:
	void Update(const WeatherInfo& info, const IObservable<WeatherInfo>& observable) override;

	InnerWeatherStation& m_station;
};
