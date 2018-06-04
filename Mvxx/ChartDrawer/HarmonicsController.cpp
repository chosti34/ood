#include "stdafx.h"
#include "HarmonicsController.h"
#include "AddHarmonicDialog.h"

namespace
{
std::vector<wxRealPoint> CalculateHarmonicWaveSum(
	const HarmonicsCollection& harmonics, float from, float to, float step)
{
	std::vector<wxRealPoint> points;
	if (harmonics.GetCount() == 0)
	{
		return points;
	}

	for (float x = from; x <= to; x += step)
	{
		points.emplace_back(x, harmonics.CalculateValue(x));
	}
	return points;
}
}

HarmonicsController::HarmonicsController(MainFrame* mainWnd, const std::shared_ptr<HarmonicsCollection>& harmonics)
	: m_harmonics(harmonics)
	, m_mainWnd(mainWnd)
	, m_selectionView(mainWnd->GetMainPanel()->GetSelectionPanel())
	, m_propertiesView(mainWnd->GetMainPanel()->GetEditorPanel())
	, m_canvasView(mainWnd->GetMainPanel()->GetViewPanel())
{
	m_connections.push_back(m_selectionView->DoOnHarmonicInsertionClick(
		std::bind(&HarmonicsController::OnHarmonicInsertionButtonClick, this)));
	m_connections.push_back(m_selectionView->DoOnHarmonicDeletionClick(
		std::bind(&HarmonicsController::OnHarmonicDeletionButtonClick, this)));
	m_connections.push_back(m_selectionView->DoOnHarmonicSelectionClick(
		std::bind(&HarmonicsController::OnHarmonicSelectionClick, this)));
	m_connections.push_back(m_harmonics->DoOnHarmonicInsertion(
		std::bind(&HarmonicsController::OnHarmonicInsertion, this)));
	m_connections.push_back(m_harmonics->DoOnHarmonicDeletion(
		std::bind(&HarmonicsController::OnHarmonicDeletion, this)));
	m_connections.push_back(m_propertiesView->DoOnHarmonicPropertiesChange(
		std::bind(&HarmonicsController::OnHarmonicPropertiesChange, this)));
}

void HarmonicsController::OnHarmonicInsertionButtonClick()
{
	Harmonic harmonic;
	AddHarmonicDialog* dlg = new AddHarmonicDialog("Add New Harmonic", wxSize(280, 270), harmonic);
	if (dlg->ShowModal() == wxID_OK)
	{
		m_selectionView->GetListBox()->Append(harmonic.ToString());
		m_harmonics->InsertHarmonic(harmonic);
	}
	dlg->Destroy();
}

void HarmonicsController::OnHarmonicDeletionButtonClick()
{
	const int selection = m_selectionView->GetListBox()->GetSelection();
	if (selection != -1)
	{
		m_selectionView->GetListBox()->Delete(selection);
		m_harmonics->DeleteHarmonic(static_cast<size_t>(selection));
	}
}

void HarmonicsController::OnHarmonicSelectionClick()
{
	m_propertiesView->Enable(true);
	const int selection = m_selectionView->GetListBox()->GetSelection();
	assert(selection != -1);
	m_propertiesView->SetHarmonicProperties(m_harmonics->GetHarmonic(selection));
}

void HarmonicsController::OnHarmonicPropertiesChange()
{
	const int selection = m_selectionView->GetListBox()->GetSelection();
	assert(selection != -1);
	m_harmonics->SetHarmonic(m_propertiesView->GetHarmonicProperties(), selection);
	m_selectionView->GetListBox()->SetString(
		static_cast<unsigned>(selection), m_propertiesView->GetHarmonicProperties().ToString());
	m_canvasView->SetPoints(CalculateHarmonicWaveSum(*m_harmonics, 0.f, 10.f, 0.01f));
	m_canvasView->Refresh(true);
}

void HarmonicsController::OnHarmonicInsertion()
{
	m_canvasView->SetPoints(CalculateHarmonicWaveSum(*m_harmonics, 0.f, 10.f, 0.01f));
	m_canvasView->Refresh(true);
}

void HarmonicsController::OnHarmonicDeletion()
{
	m_propertiesView->Enable(false);
	m_canvasView->SetPoints(CalculateHarmonicWaveSum(*m_harmonics, 0.f, 10.f, 0.01f));
	m_canvasView->Refresh(true);
}
