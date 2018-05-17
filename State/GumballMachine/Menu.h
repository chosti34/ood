#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <functional>

class Menu
{
	using Command = std::function<void(std::istream&)>;

	struct Item
	{
		Item(
			const std::string& shortcut,
			const std::string& description,
			const Command& command)
			: shortcut(shortcut)
			, description(description)
			, command(command)
		{
		}

		std::string shortcut;
		std::string description;
		Command command;
	};

public:
	Menu()
		: m_exit(false)
	{
	}

	void AddItem(
		const std::string& shortcut,
		const std::string& description,
		const Command& command)
	{
		m_items.emplace_back(shortcut, description, command);
	}

	void Run()
	{
		ShowInstructions();

		std::string command;
		while (!m_exit && std::cout << ">>> " && getline(std::cin, command))
		{
			if (!ExecuteCommand(command))
			{
				std::cout << "Unknown command\n";
			}
		}
	}

	void ShowInstructions()
	{
		std::cout << "Commands list:\n";
		for (auto & item : m_items)
		{
			std::cout << "  " << item.shortcut << ": " << item.description << "\n";
		}
	}

	void Exit()
	{
		m_exit = true;
	}

private:
	bool ExecuteCommand(const std::string& command)
	{
		std::istringstream strm(command);
		std::string shortcut;
		strm >> shortcut;

		auto found = std::find_if(m_items.begin(), m_items.end(), [&shortcut](const Item& item) {
			return item.shortcut == shortcut;
		});

		if (found != m_items.end())
		{
			found->command(strm);
			return true;
		}
		return false;
	}

	std::vector<Item> m_items;
	bool m_exit;
};
