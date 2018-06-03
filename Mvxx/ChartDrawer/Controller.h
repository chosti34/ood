#pragma once
#include "Harmonics.h"
#include "MainFrame.h"

class Controller
{
public:
	Controller(MainFrame* frame, const std::shared_ptr<Harmonics>& harmonics);

private:
	void OnHarmonicSelection(int index);
	void OnHarmonicDeletion(int index);
	void OnHarmonicInsertion(const Harmonic& harmonic);

private:
	MainFrame* m_frame;
	std::shared_ptr<Harmonics> m_harmonics;
	std::vector<boost::signals2::scoped_connection> m_connections;
};
