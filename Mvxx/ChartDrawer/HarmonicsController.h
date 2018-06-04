#pragma once
#include "MainFrame.h"
#include "HarmonicsCollection.h"

class HarmonicsController
{
public:
	HarmonicsController(MainFrame* mainWnd, const std::shared_ptr<HarmonicsCollection>& harmonics);

private:
	void OnHarmonicInsertionButtonClick();
	void OnHarmonicDeletionButtonClick();
	void OnHarmonicSelectionClick();
	void OnHarmonicPropertiesChange();
	void OnHarmonicInsertion();
	void OnHarmonicDeletion();

private:
	MainFrame* m_mainWnd;
	HarmonicSelectionView* m_selectionView;
	HarmonicPropertiesView* m_propertiesView;
	HarmonicCanvasView* m_canvasView;

	std::shared_ptr<HarmonicsCollection> m_harmonics;
	std::vector<boost::signals2::scoped_connection> m_connections;
};
