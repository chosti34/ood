#pragma once
#include <string>
#include <vector>
#include <functional>

class Menu
{
	using Command = std::function<void(std::istream& strm)>;

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

	void Run();
	void Exit();

	void ShowInstructions()const;

private:
	bool ExecuteCommand(const std::string& command);

	std::vector<Item> m_items;
	bool m_exit;
};
