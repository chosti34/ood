#pragma once
#include "IDocument.h"
#include "Menu.h"

class DocumentMenu : public Menu
{
public:
	DocumentMenu(std::istream& input, std::ostream& output, IDocument& document);

private:
	bool EnsureArgumentsCount(const uint64_t& expected, const uint64_t& count);

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
};
