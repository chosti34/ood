#include "stdafx.h"
#include "DocumentMenu.h"
#include "Document.h"
#include "ImageFileStorage.h"

int main(int, char*[])
{
	try
	{
		auto storage = std::make_unique<ImageFileStorage>();
		auto document = std::make_unique<Document>(*storage);
		auto documentMenu = std::make_unique<DocumentMenu>(*document, *storage, std::cout);
		documentMenu->Run(std::cin);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
