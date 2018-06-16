#pragma once
#include "Signals.h"

template <typename T>
class IPropertiesView
{
public:
	using PropertiesChangeSignal = Signal<void(const T&, int)>;

	virtual SignalConnection DoOnPropertiesChange(typename PropertiesChangeSignal::slot_type callback) = 0;
	virtual void SetProperties(const T& properties, int index) = 0;

	virtual void Activate(bool activate) = 0;
	virtual ~IPropertiesView() = default;
};
