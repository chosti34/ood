#pragma once
#include "MainFrame.h"
#include "HarmonicsCollection.h"

class HarmonicsController
{
public:
	HarmonicsController(MainFrame* mainWnd, const std::shared_ptr<HarmonicsCollection>& harmonics);

private:
	// View callbacks
	void OnHarmonicInsertionButtonClick();
	void OnHarmonicDeletionButtonClick(int selection);
	void OnHarmonicSelectionClick(int selection);
	void OnHarmonicDeselectionClick();
	void OnHarmonicPropertiesChangeClick(const Harmonic& harmonic);

	// Model callbacks
	void OnHarmonicInsertion();
	void OnHarmonicDeletion();
	void OnHarmonicPropertiesChange();

private:
	MainFrame* m_mainWnd;
	HarmonicSelectionView* m_selectionView;
	HarmonicPropertiesView* m_propertiesView;
	HarmonicCanvasView* m_canvasView;
	std::shared_ptr<HarmonicsCollection> m_harmonics;
	std::vector<SignalScopedConnection> m_connections;
};
