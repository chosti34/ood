#include "stdafx.h"
#include "Menu.h"

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

bool Menu::ExecuteCommand(const std::string& command)
{
	std::istringstream strm(command);
	std::string shortcut;
	strm >> shortcut;

	auto found = std::find_if(m_items.begin(), m_items.end(), [&shortcut](const Item& item) {
		return item.shortcut == shortcut;
	});

	if (found != m_items.end())
	{
		found->command(command);
		return true;
	}
	return false;
}

void Menu::Exit()
{
	m_exit = true;
}

void Menu::ShowInstructions()const
{
	std::cout << "Commands list:\n";
	for (auto& item : m_items)
	{
		std::cout << "  " << item.shortcut << " - " << item.description << "\n";
	}
}

bool Menu::IsExit()const
{
	return m_exit;
}
