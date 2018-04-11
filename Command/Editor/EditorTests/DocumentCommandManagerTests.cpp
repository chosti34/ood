#include "stdafx.h"
#include "../IDocumentCommand.h"
#include "../IDocumentCommandControl.h"
#include "../DocumentCommandManager.h"
#include <vector>

namespace
{
constexpr unsigned COMMAND_HISTORY_DEPTH = 5u;

class DocumentCommandControlMock : public IDocumentCommandControl
{
public:
	void DoInsertItem(const std::shared_ptr<DocumentItem>&, boost::optional<size_t>) override
	{
	}
	std::shared_ptr<DocumentItem> DoRemoveItem(boost::optional<size_t>) override
	{
		return std::shared_ptr<DocumentItem>();
	}
	void DoSetTitle(const std::string&) override
	{
	}
	void DoReplaceText(const std::string&, size_t) override
	{
	}
	void DoResizeImage(unsigned, unsigned, size_t) override
	{
	}
};

class CommandMock : public IDocumentCommand
{
public:
	CommandMock(std::vector<std::string> & values, int value)
		: m_values(values)
		, m_value(value)
	{
	}

	void Execute(IDocumentCommandControl&) override
	{
		m_values.push_back("Ex" + std::to_string(m_value));
	}

	void Unexecute(IDocumentCommandControl&) override
	{
		m_values.push_back("Unex" + std::to_string(m_value));
	}

private:
	std::vector<std::string> & m_values;
	int m_value;
};

struct DocumentCommandManagerFixture
{
public:
	DocumentCommandManagerFixture()
		: commandManager(COMMAND_HISTORY_DEPTH)
	{
	}

	std::vector<std::string> output;
	DocumentCommandManager commandManager;
	DocumentCommandControlMock control;
};
}

BOOST_FIXTURE_TEST_SUITE(CDocumentCommandManager, DocumentCommandManagerFixture)
	BOOST_AUTO_TEST_CASE(when_created_undo_and_redo_commands_are_not_available)
	{
		BOOST_CHECK(!commandManager.CanRedo());
		BOOST_CHECK(!commandManager.CanUndo());
	}

	BOOST_AUTO_TEST_CASE(undo_and_redo_methods_throws_exceptions_if_they_are_not_available)
	{
		BOOST_REQUIRE_THROW(commandManager.Undo(control), std::logic_error);
		BOOST_REQUIRE_THROW(commandManager.Redo(control), std::logic_error);
	}

	BOOST_AUTO_TEST_CASE(undoing_available_only_after_registering_command_and_redoing_only_after_undoing)
	{
		commandManager.RegisterCommand(std::make_unique<CommandMock>(output, 0));
		BOOST_CHECK(commandManager.CanUndo());
		BOOST_CHECK(!commandManager.CanRedo());

		commandManager.Undo(control);
		BOOST_CHECK(!commandManager.CanUndo());
		BOOST_CHECK(commandManager.CanRedo());

		commandManager.Redo(control);
		BOOST_CHECK(commandManager.CanUndo());
		BOOST_CHECK(!commandManager.CanRedo());
	}

	BOOST_AUTO_TEST_CASE(clears_redo_stack_when_executing_new_command)
	{
		for (int i = 0; i < 3; ++i)
		{
			commandManager.RegisterCommand(std::make_unique<CommandMock>(output, 0));
		}

		for (int i = 0; i < 2; ++i)
		{
			BOOST_CHECK(commandManager.CanUndo());
			commandManager.Undo(control);
		}

		BOOST_CHECK(commandManager.CanRedo());
		commandManager.RegisterCommand(std::make_unique<CommandMock>(output, 0));
		BOOST_CHECK(!commandManager.CanRedo());
	}

	BOOST_AUTO_TEST_CASE(command_count_can_never_be_more_than_history_depth_value)
	{
		// Выполняем 6 команд
		for (int i = 1; i <= 6; ++i)
		{
			auto command = std::make_unique<CommandMock>(output, i);
			command->Execute(control);
			commandManager.RegisterCommand(std::move(command));
		}

		std::vector<std::string> expected = { "Ex1", "Ex2", "Ex3", "Ex4", "Ex5", "Ex6" };
		BOOST_CHECK(output == expected);
		output.clear();

		while (commandManager.CanUndo())
		{
			commandManager.Undo(control);
		}

		// Убеждаемся, что отменено было лишь пять последних команд
		expected = { "Unex6", "Unex5", "Unex4", "Unex3", "Unex2" };
		BOOST_CHECK(output == expected);
	}
BOOST_AUTO_TEST_SUITE_END()
