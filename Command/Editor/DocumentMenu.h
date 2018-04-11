#pragma once
#include "IDocument.h"
#include "Menu.h"
class ImageFileStorage;

class DocumentMenu : public Menu
{
public:
	DocumentMenu(IDocument& document, ImageFileStorage& storage);

private:
	bool EnsureArgumentsCount(uint64_t expected, uint64_t count);

	void SetDocumentTitle(std::vector<std::string> const& args);
	void InsertParagraph(std::vector<std::string> const& args);
	void InsertImage(std::vector<std::string> const& args);
	void List(std::vector<std::string> const& args);
	void ReplaceText(std::vector<std::string> const& args);
	void ResizeImage(std::vector<std::string> const& args);
	void DeleteItem(std::vector<std::string> const& args);
	void Save(std::vector<std::string> const& args);
	void Undo(std::vector<std::string> const& args);
	void Redo(std::vector<std::string> const& args);

private:
	IDocument& m_document;
	ImageFileStorage& m_storage;
};
