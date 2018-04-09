#include "stdafx.h"
#include "DocumentMenu.h"
#include "Document.h"

int main(int, char*[])
{
	try
	{
		auto document = std::make_unique<Document>();
		auto documentMenu = std::make_unique<DocumentMenu>(*document);
		documentMenu->Run();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
