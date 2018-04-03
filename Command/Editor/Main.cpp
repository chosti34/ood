#include "stdafx.h"
#include "Document.h"
#include "CommandFactory.h"
#include "ICommand.h"
#include "Menu.h"

void BindConsoleCommands(Menu& menu, ICommandFactory& factory, Document& document)
{
	menu.AddItem("exit", "exit the menu: <no args>",
		[&menu](const std::string& command) {
			(void)command;
			menu.Exit();
		}
	);
	menu.AddItem(
		"insertph", "insert paragraph into document: <pos>|end <text>",
		[&factory, &document](const std::string& command) {
			document.OnCommand(std::move(factory.CreateCommand(command)));
		}
	);
}

void ExecuteMainLoop(Menu& menu)
{
	menu.ShowInstructions();

	std::string command;
	while (!menu.IsExit() && std::cout << "> " && getline(std::cin, command))
	{
		bool found = menu.ExecuteCommand(command);
		if (!found)
		{
			std::cout << "Unknown command!" << std::endl;
		}
	}
}

int main(int argc, char* argv[])
{
	(void)argc;
	(void)argv;

	try
	{
		Menu menu;
		CommandFactory factory;
		Document document;

		BindConsoleCommands(menu, factory, document);
		ExecuteMainLoop(menu);
	}
	catch (const std::exception& ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
