#include "stdafx.h"
#include "HarmonicsController.h"
#include "AddHarmonicDialog.h"
#include "SharedUI.h"

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
}

HarmonicsController::HarmonicsController(
	const std::shared_ptr<HarmonicsCollection>& harmonics,
	ISelectionView<Harmonic>* selectionView,
	IPropertiesView<Harmonic>* propertiesView,
	ICanvasView* canvasView,
	ITableView* tableView)
	: m_harmonics(harmonics)
	, m_selectionView(selectionView)
	, m_propertiesView(propertiesView)
	, m_canvasView(canvasView)
	, m_tableView(tableView)
{
	namespace ph = std::placeholders;
	m_connections.emplace_back(m_selectionView->DoOnAppend(std::bind(
		&HarmonicsController::OnHarmonicInsertionButtonClick, this)));
	m_connections.emplace_back(m_selectionView->DoOnDeletion(std::bind(
		&HarmonicsController::OnHarmonicDeletionButtonClick, this, ph::_1)));
	m_connections.emplace_back(m_selectionView->DoOnSelection(std::bind(
		&HarmonicsController::OnHarmonicSelectionClick, this, ph::_1)));
	m_connections.emplace_back(m_selectionView->DoOnDeselection(std::bind(
		&HarmonicsController::OnHarmonicDeselectionClick, this)));
	m_connections.emplace_back(m_propertiesView->DoOnPropertiesChange(std::bind(
		&HarmonicsController::OnHarmonicPropertiesChangeClick, this, ph::_1, ph::_2)));
	m_connections.emplace_back(m_harmonics->DoOnHarmonicInsertion(
		std::bind(&HarmonicsController::OnHarmonicInsertion, this)));
	m_connections.emplace_back(m_harmonics->DoOnHarmonicDeletion(
		std::bind(&HarmonicsController::OnHarmonicDeletion, this)));
	m_connections.emplace_back(m_harmonics->DoOnHarmonicPropertiesChange(
		std::bind(&HarmonicsController::OnHarmonicPropertiesChange, this)));
}

void HarmonicsController::OnHarmonicInsertionButtonClick()
{
	Harmonic harmonic;
	AddHarmonicDialog* dlg = new AddHarmonicDialog("Add New Harmonic", wxSize(280, 270), harmonic);
	if (dlg->ShowModal() == wxID_OK)
	{
		m_selectionView->Append(harmonic);
		m_harmonics->InsertHarmonic(harmonic);
	}
	dlg->Destroy();
}

void HarmonicsController::OnHarmonicDeletionButtonClick(int selection)
{
	m_selectionView->DeleteElementAt(selection);
	m_harmonics->DeleteHarmonic(static_cast<size_t>(selection));
	m_propertiesView->Activate(false);
}

void HarmonicsController::OnHarmonicSelectionClick(int selection)
{
	m_propertiesView->Activate(true);
	m_propertiesView->SetProperties(m_harmonics->GetHarmonic(selection), selection);
}

void HarmonicsController::OnHarmonicDeselectionClick()
{
	m_propertiesView->Activate(false);
}

void HarmonicsController::OnHarmonicPropertiesChangeClick(const Harmonic& harmonic, int index)
{
	assert(index >= 0 && index < m_harmonics->GetCount());
	m_selectionView->SetElementAt(harmonic, static_cast<size_t>(index));
	m_harmonics->SetHarmonic(harmonic, static_cast<size_t>(index));
}

void HarmonicsController::OnHarmonicInsertion()
{
	RecalculateHarmonics();
}

void HarmonicsController::OnHarmonicDeletion()
{
	RecalculateHarmonics();
}

void HarmonicsController::OnHarmonicPropertiesChange()
{
	RecalculateHarmonics();
}

void HarmonicsController::RecalculateHarmonics()
{
	const float step = 0.01f;
	const float from = 0.f;
	const float to = m_canvasView->GetDrawingAreaSize().x / SharedUI::PIXELS_PER_UNIT.x;

	const auto points = CalculateHarmonicWaveSum(*m_harmonics, from, to, step);
	m_canvasView->SetPixelPoints(ConvertToPixelPoints(points, SharedUI::PIXELS_PER_UNIT));
	m_tableView->SetPoints(points);
}
