#include "stdafx.h"
#include "SimpleDisplay.h"

SimpleDisplay::SimpleDisplay()
{
}

SimpleDisplay::~SimpleDisplay()
{
}

void SimpleDisplay::Update(const WeatherInfo& data, IObservable<WeatherInfo>& observable)
{
	// ������ ������ �� ������������ � ����������� ���������
	std::cout << "Simple display update:" << std::endl;
	std::cout << "Current Temperature " << data.temperature << std::endl;
	std::cout << "Current Pressure " << data.pressure << std::endl;
	std::cout << "----------------" << std::endl;
}
