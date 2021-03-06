#include "stdafx.h"
#include "DocumentMenu.h"
#include "Document.h"
#include "ImageFileStorage.h"

namespace
{
const std::string DEFAULT_DOCUMENT_TITLE = "untitled";
}

int main(int, char*[])
{
	try
	{
		auto document = std::make_unique<Document>(DEFAULT_DOCUMENT_TITLE);
		auto menu = std::make_unique<DocumentMenu>(std::cin, std::cout, *document);
		menu->Run();
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
