#include "stdafx.h"
#include "HarmonicsController.h"

HarmonicsController::HarmonicsController(MainFrame* frame, const std::shared_ptr<HarmonicsCollection>& harmonics)
	: m_frame(frame)
	, m_harmonics(harmonics)
	, m_selectionView(frame->GetMainPanel()->GetSelectionPanel())
	, m_propertiesView(frame->GetMainPanel()->GetEditorPanel())
	, m_canvasView(frame->GetMainPanel()->GetViewPanel())
{
}

void HarmonicsController::OnHarmonicSelection(int index)
{
	m_propertiesView->Enable(true);
	m_propertiesView->SetHarmonicProperties(m_harmonics->GetHarmonic(index));
}

void HarmonicsController::OnHarmonicDeletion(int index)
{
	m_propertiesView->Enable(false);
	// recalculate everything
	m_canvasView->Refresh(true);
}

void HarmonicsController::OnHarmonicInsertion(const Harmonic& harmonic)
{
	m_harmonics->InsertHarmonic(harmonic);
}
