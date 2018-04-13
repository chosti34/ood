#pragma once
#include "AbstractCommand.h"
#include "IDocumentCommandControl.h"
#include "ICommandManager.h"
#include "IImageFileStorage.h"
#include <boost/optional.hpp>
#include <string>

class InsertImageCommand final : public AbstractCommand
{
public:
	InsertImageCommand(
		IDocumentCommandControl& control,
		ICommandManager& manager,
		unsigned width, unsigned height,
		const std::string& path,
		boost::optional<size_t> position,
		IImageFileStorage& storage);
	~InsertImageCommand();

private:
	void ExecuteImpl() override;
	void UnexecuteImpl() override;

private:
	IDocumentCommandControl& m_control;
	ICommandManager& m_manager;
	unsigned m_width;
	unsigned m_height;
	std::string m_path;
	boost::optional<size_t> m_position;
	std::shared_ptr<DocumentItem> m_item;
	IImageFileStorage& m_storage;
};
