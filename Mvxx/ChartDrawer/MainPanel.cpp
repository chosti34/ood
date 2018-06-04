#include "stdafx.h"
#include "MainPanel.h"

MainPanel::MainPanel(wxFrame* frame)
	: wxPanel(frame)
{
	CreateControls();
	RegisterEventHandlers();
}

HarmonicSelectionView* MainPanel::GetSelectionPanel()
{
	return m_selectionPanel;
}

HarmonicPropertiesView* MainPanel::GetEditorPanel()
{
	return m_editorPanel;
}

HarmonicCanvasView* MainPanel::GetViewPanel()
{
	return m_viewPanel;
}

void MainPanel::CreateControls()
{
	wxBoxSizer* mainSizer = new wxBoxSizer(wxVERTICAL);
	wxBoxSizer* upperSizer = new wxBoxSizer(wxHORIZONTAL);

	m_selectionPanel = new HarmonicSelectionView(this);
	upperSizer->Add(m_selectionPanel, 1, wxEXPAND | wxLEFT | wxTOP, 5);

	m_editorPanel = new HarmonicPropertiesView(this);
	upperSizer->Add(m_editorPanel, 1, wxEXPAND | wxLEFT | wxTOP | wxRIGHT, 5);
	m_editorPanel->Disable();

	mainSizer->Add(upperSizer, 1, wxEXPAND, 0);
	m_viewPanel = new HarmonicCanvasView(this);
	mainSizer->Add(m_viewPanel, 1, wxEXPAND | wxALL, 5);

	SetSizerAndFit(mainSizer);
}

void MainPanel::RegisterEventHandlers()
{
	m_connections.push_back(m_selectionPanel->DoOnHarmonicSelection([this](int index) {
		assert(index >= 0 && index < m_harmonics.size());
		m_editorPanel->Enable();
		m_editorPanel->SetHarmonicProperties(m_harmonics[index]);
		std::cout << "Harmonics count: " << m_harmonics.size() << std::endl;
	}));

	m_connections.push_back(m_selectionPanel->DoOnHarmonicDeletion([this](int index) {
		assert(index >= 0 && index < m_harmonics.size());
		m_editorPanel->Disable();
		m_harmonics.erase(m_harmonics.begin() + index);
		m_viewPanel->SetPoints(CalculatePoints(0.f, 20.f, 0.02f));
		m_viewPanel->Refresh();
		std::cout << "Harmonics count: " << m_harmonics.size() << std::endl;
	}));

	m_connections.push_back(m_selectionPanel->DoOnHarmonicInsertion([this](const Harmonic& harmonic) {
		m_harmonics.push_back(harmonic);
		m_viewPanel->SetPoints(CalculatePoints(0.f, 20.f, 0.02f));
		m_viewPanel->Refresh();
		std::cout << "Harmonics count: " << m_harmonics.size() << std::endl;
	}));

	m_connections.push_back(m_editorPanel->DoOnHarmonicAttributesChange([this]() {
		int selection = m_selectionPanel->GetListBoxSelectionIndex();
		assert(selection != -1); // при измении данных в панели редактирования гармоники должен быть выделен элемент списка
		m_selectionPanel->SetStringAtListBoxItem(m_editorPanel->GetHarmonicProperties().ToString(), selection);
		m_harmonics[selection] = m_editorPanel->GetHarmonicProperties();
		m_viewPanel->SetPoints(CalculatePoints(0.f, 20.f, 0.02f));
		m_viewPanel->Refresh();
	}));
}

std::vector<wxRealPoint> MainPanel::CalculatePoints(float lowerBound, float upperBound, float eps)
{
	std::vector<wxRealPoint> points;
	if (m_harmonics.empty())
	{
		return points;
	}

	for (float x = lowerBound; x <= upperBound; x += eps)
	{
		float value = 0.f;
		for (const auto& harmonic : m_harmonics)
		{
			value += harmonic.GetValue(x);
		}
		points.push_back(wxRealPoint(x, value));
	}
	return points;
}
