#include "stdafx.h"
#include "Document.h"
#include "DocumentInputControl.h"

int main(int /* argc */, char* /* argv */[])
{
	try
	{
		auto menu = std::make_unique<Menu>();
		auto document = std::make_unique<Document>();
		DocumentInputControl control(*document, *menu);
		menu->Run();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
