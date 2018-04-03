#pragma once
#include <string>
#include <vector>
#include <functional>

class Menu
{
	using Command = std::function<void(const std::string&)>;

	struct Item
	{
		Item(
			const std::string& shortcut,
			const std::string& description,
			Command&& command);

		std::string shortcut;
		std::string description;
		Command command;
	};

public:
	Menu();

	void AddItem(
		const std::string& shortcut,
		const std::string& description,
		Command&& command);

	bool ExecuteCommand(const std::string& command);
	void Exit();

	void ShowInstructions()const;
	bool IsExit()const;

private:
	std::vector<Item> m_items;
	bool m_exit;
};
