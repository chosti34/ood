#pragma once
#include "MainFrame.h"
#include "HarmonicsCollection.h"

//  ласс контроллера или презентера знает про модель и про представление,
//  хран€ указатели на соответствующие их экземпл€ры. — помощью контроллера
//  происходит св€зывание модели и представлени€, которые ничего друг о друге
//  знать не должны. “аким образом, основна€ суть паттерна - создать классы представлени€
//  и модели, и затем их св€зать контроллером
class HarmonicsController
{
public:
	HarmonicsController(MainFrame* frame, const std::shared_ptr<HarmonicsCollection>& harmonics);

private:
	void OnHarmonicSelection(int index);
	void OnHarmonicDeletion(int index);
	void OnHarmonicInsertion(const Harmonic& harmonic);

private:
	MainFrame* m_frame;
	HarmonicSelectionView* m_selectionView;
	HarmonicPropertiesView* m_propertiesView;
	HarmonicCanvasView* m_canvasView;

	std::shared_ptr<HarmonicsCollection> m_harmonics;
	std::vector<boost::signals2::scoped_connection> m_connections;
};
