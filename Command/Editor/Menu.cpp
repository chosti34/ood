#include "stdafx.h"
#include "Menu.h"

namespace
{
std::vector<std::string> Tokenize(std::istream& strm)
{
	using namespace std;
	using Iterator = istream_iterator<string>;
	vector<string> tokens;
	copy(Iterator(strm), Iterator(), back_inserter(tokens));
	return tokens;
}
}

Menu::Item::Item(
	const std::string& shortcut,
	const std::string& description,
	Command&& command)
	: shortcut(shortcut)
	, description(description)
	, command(std::move(command))
{
}

Menu::Menu()
	: m_items()
	, m_exit(false)
{
}

void Menu::AddItem(
	const std::string& shortcut,
	const std::string& description,
	Command&& command)
{
	m_items.emplace_back(shortcut, description, std::move(command));
}

void Menu::Run()
{
	ShowInstructions();

	std::string command;
	while (!m_exit && std::cout << ">>> " && getline(std::cin, command))
	{
		try
		{
			ExecuteCommand(command);
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what() << std::endl;
		}
	}
}

void Menu::Exit()
{
	m_exit = true;
}

void Menu::ShowInstructions()const
{
	std::cout << "Commands list:" << std::endl;
	for (size_t i = 0u; i < m_items.size(); ++i)
	{
		const auto index = i + 1;
		const auto& shortcut = m_items[i].shortcut;
		const auto& description = m_items[i].description;
		std::cout << "  " << index << ". " << shortcut << " - " << description << std::endl;
	}
}

void Menu::ExecuteCommand(const std::string& command)
{
	std::istringstream strm(command);
	std::string shortcut;
	strm >> shortcut;

	auto found = std::find_if(m_items.begin(), m_items.end(), [&shortcut](const Item& item) {
		return item.shortcut == shortcut;
	});

	if (found != m_items.end())
	{
		auto& fn = found->command;
		fn(Tokenize(strm));
	}
	else
	{
		std::cout << "Unknown command!" << std::endl;
	}
}
