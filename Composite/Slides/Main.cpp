#include "stdafx.h"
#include "MainFrm.h"
#include "DrawingPanel.h"

#include "../Shapes/Color.h"
#include "../Shapes/IFillStyle.h"
#include "../Shapes/IOutlineStyle.h"

#include "../Shapes/Slide.h"
#include "../Shapes/Ellipse.h"
#include "../Shapes/Triangle.h"
#include "../Shapes/Rectangle.h"
#include "../Shapes/CompositeShape.h"

namespace
{
std::shared_ptr<ISlide> CreateBeautifulSlide(float width, float height)
{
	auto slide = std::make_shared<Slide>(width, height, MapRGB(0x00, 0xbf, 0xff));

	auto sun = std::make_shared<shapelib::Ellipse>(
		Point2D{0.65f * width, 0.25f * height}, 50.f, 50.f);
	sun->GetFillStyle().SetColor(MapRGB(0xff, 0xff, 0x00));
	sun->GetOutlineStyle().SetColor(MapRGB(0xff, 0xa5, 0x00));

	auto ground = std::make_shared<shapelib::Rectangle>(
		Point2D{0, 0.8f * height}, width, 0.2f * height);
	ground->GetFillStyle().SetColor(MapRGB(0xff, 0x99, 0x66));
	ground->GetOutlineStyle().SetColor(MapRGB(0x00, 0x00, 0x00));

	auto lake = std::make_shared<shapelib::Ellipse>(
		Point2D{0.65f * width, 0.9f * height}, 70.f, 20.f);
	lake->GetFillStyle().SetColor(MapRGB(0x33, 0x99, 0xff));
	lake->GetOutlineStyle().SetColor(MapRGB(0x55, 0x55, 0x55));

	auto house = std::make_shared<CompositeShape>();

	auto foundation = std::make_shared<shapelib::Rectangle>(
		Point2D{ 0.15f * width, 0.6f * height }, 0.3f * width, 0.25f * height);
	foundation->GetFillStyle().SetColor(MapRGB(0xcc, 0x66, 0x00));
	foundation->GetOutlineStyle().SetColor(MapRGB(0x00, 0x00, 0x00));

	auto pipe = std::make_shared<shapelib::Rectangle>(
		Point2D{0.33f * width, 0.4f * height}, 30.f, 50.f);
	pipe->GetFillStyle().SetColor(MapRGB(0xff, 0x00, 0x00));
	pipe->GetOutlineStyle().SetColor(MapRGB(0x00, 0x00, 0x00));

	auto roof = std::make_shared<shapelib::Triangle>(
		Point2D{ 0.12f * width, 0.6f * height },
		Point2D{ 0.3f * width, 0.4f * height },
		Point2D{ 0.47f * width, 0.6f * height });
	roof->GetFillStyle().SetColor(MapRGB(0x55, 0x55, 0x55));
	roof->GetOutlineStyle().SetColor(MapRGB(0x77, 0x77, 0x77));

	house->InsertShape(foundation);
	house->InsertShape(pipe);
	house->InsertShape(roof);

	auto frame = house->GetFrame();
	house->SetFrame(RectF{ frame.left, frame.top - 100, frame.width * 2, frame.height });
	house->GetOutlineStyle().SetColor(MapRGB(0xff, 0xff, 0x00));
	house->GetOutlineStyle().SetThickness(2.f);

	slide->GetShapes().InsertShape(ground);
	slide->GetShapes().InsertShape(sun);
	slide->GetShapes().InsertShape(lake);
	slide->GetShapes().InsertShape(house);

	return slide;
}

class GdiplusInitializer
{
public:
	GdiplusInitializer()
	{
		Gdiplus::GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, nullptr);
	}

	~GdiplusInitializer()
	{
		Gdiplus::GdiplusShutdown(m_gdiplusToken);
	}

private:
	Gdiplus::GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR m_gdiplusToken;
};

class App : public wxApp
{
public:
	App()
		: m_slide(CreateBeautifulSlide(800, 600))
	{
	}

	bool OnInit()wxOVERRIDE
	{
		MainFrm* frame = new MainFrm("Slides");
		DrawingPanel* panel = new DrawingPanel(frame);

		frame->SetClientSize(wxRect(0, 0, 800, 600));
		frame->Centre();
		frame->Show();

		panel->AddDrawable(m_slide);
		return true;
	}

private:
	GdiplusInitializer gdiplus;
	std::shared_ptr<ISlide> m_slide;
};
}

#ifndef _DEBUG
	wxIMPLEMENT_APP(App);
#else
	wxIMPLEMENT_APP_CONSOLE(App);
#endif
