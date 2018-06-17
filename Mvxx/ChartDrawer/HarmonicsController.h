#pragma once
#include "ISelectionView.h"
#include "IPropertiesView.h"
#include "ICanvasView.h"
#include "ITableView.h"
#include "HarmonicsCollection.h"

class HarmonicsController
{
public:
	HarmonicsController(
		const std::shared_ptr<HarmonicsCollection>& harmonics,
		ISelectionView<Harmonic>* selectionView,
		IPropertiesView<Harmonic>* propertiesView,
		ICanvasView* canvasView,
		ITableView* tableView);

private:
	void OnHarmonicInsertionButtonClick();
	void OnHarmonicDeletionButtonClick(int selection);
	void OnHarmonicSelectionClick(int selection);
	void OnHarmonicDeselectionClick();
	void OnHarmonicPropertiesChangeClick(const Harmonic& harmonic, int index);
	void OnHarmonicInsertion();
	void OnHarmonicDeletion();
	void OnHarmonicPropertiesChange();

	void RecalculateHarmonics();

private:
	ISelectionView<Harmonic>* m_selectionView;
	IPropertiesView<Harmonic>* m_propertiesView;
	ICanvasView* m_canvasView;
	ITableView* m_tableView;
	std::shared_ptr<HarmonicsCollection> m_harmonics;
	std::vector<SignalScopedConnection> m_connections;
};
