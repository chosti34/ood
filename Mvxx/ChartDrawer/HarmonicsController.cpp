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

std::vector<wxRealPoint> ConvertToPixelPoints(
	const std::vector<wxRealPoint>& points, const wxRealPoint& pixelsCountPerRealUnit)
{
	std::vector<wxRealPoint> pixelPoints(points.size());
	std::transform(points.begin(), points.end(), pixelPoints.begin(), [&](const wxRealPoint& point) {
		return wxRealPoint{ point.x * pixelsCountPerRealUnit.x, -point.y * pixelsCountPerRealUnit.y };
	});
	return pixelPoints;
}

const float FROM = 0.f;
const float TO = 8.f;
const float STEP = 0.01f;
}

HarmonicsController::HarmonicsController(MainFrame* mainWnd, const std::shared_ptr<HarmonicsCollection>& harmonics)
	: m_harmonics(harmonics)
	, m_mainWnd(mainWnd)
	, m_selectionView(mainWnd->GetMainPanel()->GetSelectionView())
	, m_propertiesView(mainWnd->GetMainPanel()->GetPropertiesView())
	, m_canvasView(mainWnd->GetMainPanel()->GetCanvasView())
{
	namespace ph = std::placeholders;
	m_connections.emplace_back(m_selectionView->DoOnHarmonicInsertionClick(
		std::bind(&HarmonicsController::OnHarmonicInsertionButtonClick, this)));
	m_connections.emplace_back(m_selectionView->DoOnHarmonicDeletionClick(
		std::bind(&HarmonicsController::OnHarmonicDeletionButtonClick, this, ph::_1)));
	m_connections.emplace_back(m_selectionView->DoOnHarmonicSelectionClick(
		std::bind(&HarmonicsController::OnHarmonicSelectionClick, this, ph::_1)));
	m_connections.emplace_back(m_selectionView->DoOnHarmonicDeselectionClick(
		std::bind(&HarmonicsController::OnHarmonicDeselectionClick, this)));
	m_connections.emplace_back(m_harmonics->DoOnHarmonicInsertion(
		std::bind(&HarmonicsController::OnHarmonicInsertion, this)));
	m_connections.emplace_back(m_harmonics->DoOnHarmonicDeletion(
		std::bind(&HarmonicsController::OnHarmonicDeletion, this)));
	m_connections.emplace_back(m_propertiesView->DoOnHarmonicPropertiesChange(
		std::bind(&HarmonicsController::OnHarmonicPropertiesChange, this)));
}

void HarmonicsController::OnHarmonicInsertionButtonClick()
{
	Harmonic harmonic;
	AddHarmonicDialog* dlg = new AddHarmonicDialog("Add New Harmonic", wxSize(280, 270), harmonic);
	if (dlg->ShowModal() == wxID_OK)
	{
		m_selectionView->AppendHarmonic(harmonic);
		m_harmonics->InsertHarmonic(harmonic);
	}
	dlg->Destroy();
}

void HarmonicsController::OnHarmonicDeletionButtonClick(int selection)
{
	m_selectionView->DeleteHarmonic(selection);
	m_harmonics->DeleteHarmonic(static_cast<size_t>(selection));
}

void HarmonicsController::OnHarmonicSelectionClick(int selection)
{
	m_propertiesView->Enable(true);
	m_propertiesView->SetHarmonicProperties(m_harmonics->GetHarmonic(selection));
}

void HarmonicsController::OnHarmonicDeselectionClick()
{
	m_propertiesView->Enable(false);
}

void HarmonicsController::OnHarmonicPropertiesChange()
{
	const int selection = m_selectionView->GetSelection();
	assert(selection != wxNOT_FOUND);
	m_selectionView->SetHarmonic(
		m_propertiesView->GetHarmonicProperties(), static_cast<unsigned>(selection));
	m_harmonics->SetHarmonic(m_propertiesView->GetHarmonicProperties(), selection);
	m_canvasView->SetPixelPoints(ConvertToPixelPoints(
		CalculateHarmonicWaveSum(*m_harmonics, FROM, TO, STEP), wxRealPoint(100, 15)));
	m_canvasView->Refresh(true);
}

void HarmonicsController::OnHarmonicInsertion()
{
	m_canvasView->SetPixelPoints(ConvertToPixelPoints(
		CalculateHarmonicWaveSum(*m_harmonics, FROM, TO, STEP), wxRealPoint(100, 15)));
	m_canvasView->Refresh(true);
}

void HarmonicsController::OnHarmonicDeletion()
{
	m_propertiesView->Enable(false);
	m_canvasView->SetPixelPoints(ConvertToPixelPoints(
		CalculateHarmonicWaveSum(*m_harmonics, FROM, TO, STEP), wxRealPoint(100, 15)));
	m_canvasView->Refresh(true);
}
