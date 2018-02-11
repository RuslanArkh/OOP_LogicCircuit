#ifndef _FIEL_COMMAND_HANDLER_H_
#define _FILE_COMMAND_HANDLER_H_

#include <fstream>
#include <iostream>
#include <cstdio>
#include <ctype.h>

#include "component.h"

class FileCommandHandler
{

	enum ReadingState { ERROR, SETTING_INPUT, CHOOSING_PORT_FOR_INPUT, SETTING_VALUE, SHOWING_OUTPUT, CHOOSING_PORT_FOR_OUTPUT, NOTHING };

	void WriteError(std::ostream & _o, std::string const & _errStr);

public: 

	FileCommandHandler(std::unique_ptr<Component> const & _UsedComponent, std::string const & _fileName);

	void RunFileCommands(std::ostream & _o);

private:

	const std::unique_ptr<Component> & m_Component;
	std::fstream m_File;

	ReadingState m_State = ReadingState::NOTHING;

};

#endif