#pragma once
#include <iosfwd>
#include <string>
#include <vector>
#include <functional>

class Menu
{
	using Command = std::function<void(std::vector<std::string> const&)>;

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
	Menu(std::istream& input, std::ostream& output);

	void AddItem(
		const std::string& shortcut,
		const std::string& description,
		Command&& command);

	void Run();
	void Exit();
	void ShowInstructions()const;
	bool ExecuteCommand(const std::string& command);

protected:
	std::istream& m_input;
	std::ostream& m_output;

private:
	std::vector<Item> m_items;
	bool m_exit;
};
