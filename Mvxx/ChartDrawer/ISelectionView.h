#pragma once
#include "Signals.h"

template <typename T>
class ISelectionView
{
public:
	using AppendSignal = Signal<void()>;
	using DeletionSignal = Signal<void(int)>;
	using SelectionSignal = Signal<void(int)>;
	using DeselectionSignal = Signal<void()>;

	virtual SignalConnection DoOnAppend(AppendSignal::slot_type callback) = 0;
	virtual SignalConnection DoOnDeletion(DeletionSignal::slot_type callback) = 0;
	virtual SignalConnection DoOnSelection(SelectionSignal::slot_type callback) = 0;
	virtual SignalConnection DoOnDeselection(DeselectionSignal::slot_type callback) = 0;

	virtual void Append(const T& element) = 0;
	virtual void SetElementAt(const T& element, size_t index) = 0;
	virtual void DeleteElementAt(size_t index) = 0;
	virtual int GetSelection()const = 0;

	virtual ~ISelectionView() = default;
};
