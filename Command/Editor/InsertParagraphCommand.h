#pragma once
#include "AbstractCommand.h"
#include "IDocumentCommandControl.h"
#include <boost/optional.hpp>
#include <string>

class InsertParagraphCommand : public AbstractCommand
{
public:
	InsertParagraphCommand(
		IDocumentCommandControl& control,
		ICommandManager& manager,
		const std::string& text,
		boost::optional<size_t> position);

private:
	void ExecuteImpl() override;
	void UnexecuteImpl() override;

private:
	IDocumentCommandControl& m_control;
	ICommandManager& m_manager;
	std::string m_text;
	std::shared_ptr<DocumentItem> m_item;
	boost::optional<size_t> m_position;
};
