#include "stdafx.h"
#include "Controller.h"

Controller::Controller(MainFrame* frame, const std::shared_ptr<Harmonics>& harmonics)
	: m_frame(frame)
	, m_harmonics(harmonics)
{
	m_frame->GetMainPanel()->SetHarmonics(m_harmonics);

	HarmonicSelectionPanel* selectionPanel = m_frame->GetMainPanel()->GetSelectionPanel();
	HarmonicEditorPanel* editorPanel = m_frame->GetMainPanel()->GetEditorPanel();
	HarmonicViewPanel* viewPanel = m_frame->GetMainPanel()->GetViewPanel();

	m_connections.push_back(selectionPanel->DoOnHarmonicSelection([&](int index) {
		assert(index >= 0 && index < m_harmonics->GetSize());
		editorPanel->Enable();
		editorPanel->SetHarmonicData(m_harmonics->GetHarmonicAt(index));
		std::cout << "Harmonics count: " << m_harmonics->GetSize() << std::endl;
	}));

	m_connections.push_back(selectionPanel->DoOnHarmonicInsertion([](const Harmonic& harmonic) {

	}));
}

void Controller::OnHarmonicSelection(int index)
{
	assert(index >= 0 && index < m_harmonics->GetSize());
	HarmonicEditorPanel* editorPanel = m_frame->GetMainPanel()->GetEditorPanel();
	editorPanel->Enable();
	editorPanel->SetHarmonicData(m_harmonics->GetHarmonicAt(index));
	std::cout << "Harmonics count: " << m_harmonics->GetSize() << std::endl;
}

void Controller::OnHarmonicDeletion(int index)
{
	assert(index >= 0 && index < m_harmonics->GetSize());
	m_harmonics->DeleteHarmonicAt(index);
}

void Controller::OnHarmonicInsertion(const Harmonic & harmonic)
{
}
