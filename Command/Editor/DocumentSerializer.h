#pragma once
#include <string>
#include <vector>

class DocumentSerializer
{
public:
	DocumentSerializer();

	void SetTitle(const std::string& title);
	void AddParagraph(const std::string& text);
	void AddImage(const std::string& path, unsigned width, unsigned height);

	std::string Serialize()const;

private:
	std::vector<std::string> m_body;
	std::string m_title;
};
