#include "filecommandhandler.h"

#include <stdexcept>

const std::string SET_INPUT = "SET_INPUT";
const std::string SHOW_PORT = "SHOW_PORT";


FileCommandHandler::FileCommandHandler(std::unique_ptr<Component> const & _UsedComponent, std::string const & _fileName)
	: m_Component(std::move(_UsedComponent))
{
	m_File.open(_fileName, std::fstream::in);

	if (!m_File)
		throw std::logic_error("Current file does not exist.");

}

bool icompare_pred(unsigned char a, unsigned char b)
{
	return tolower(a) == tolower(b);
}

bool CmpStrings(std::string const& a, std::string const& b)
{
	if (a.length() == b.length()) 
		return std::equal(b.begin(), b.end(), a.begin(), icompare_pred);
	else 
		return false;
}

void FileCommandHandler::RunFileCommands(std::ostream & _o)
{
	int n = 0;
	std::string tempStr;
	std::string tempPort;
	std::string errorBuf;
	
	while (m_File >> tempStr)
	{
		++n;
		//m_File >> tempStr;
		if (m_State == ReadingState::ERROR)
		{
			std::cout << "File reading stopped!\n";
			//m_File.seekg(0, std::ios::beg);
			break;
		}
		if (tempStr == SET_INPUT || tempStr == SHOW_PORT)
		{
			if (tempStr == SET_INPUT)
				m_State = ReadingState::SETTING_INPUT;
			else if (tempStr == SHOW_PORT)
				m_State = ReadingState::SHOWING_OUTPUT;
			//m_State = (ReadingState)FileCommandHandler::m_curState.find(tempStr)->second;
			switch (m_State)
			{
			case ReadingState::SETTING_INPUT:
				m_State = ReadingState::CHOOSING_PORT_FOR_INPUT;
				break;
			case ReadingState::SHOWING_OUTPUT:
				m_State = ReadingState::CHOOSING_PORT_FOR_OUTPUT;
				break;
			default:
				break;
			}
		}
		else
		{
			switch (m_State)
			{
			case ReadingState::CHOOSING_PORT_FOR_INPUT:
				tempPort = tempStr;
				if (!m_Component.get()->findInPort(tempPort))
				{
					errorBuf += "Current port does not exist: ";
					errorBuf += tempPort;
					WriteError(std::cout, errorBuf);
					errorBuf.clear();
					m_State = ReadingState::ERROR;
				}
				else
					m_State = ReadingState::SETTING_VALUE;
				break;
			case ReadingState::SETTING_VALUE:
				if (CmpStrings(tempStr, "true"))
					m_Component.get()->SetInput(tempPort, true);
				else if (CmpStrings(tempStr, "false"))
					m_Component.get()->SetInput(tempPort, false);
				else
				{
					errorBuf += "Unknown type: ";
					errorBuf += tempStr;
					WriteError(std::cout, errorBuf);
					errorBuf.clear();
					m_State = ReadingState::ERROR;
				}
				m_State = ReadingState::NOTHING;
				break;

			case ReadingState::CHOOSING_PORT_FOR_OUTPUT:
				tempPort = tempStr;
				if (!m_Component.get()->findOutPort(tempPort))
				{
					errorBuf += "Current port does not exist: ";
					errorBuf += tempPort;
					WriteError(std::cout, errorBuf);
					errorBuf.clear();
					m_State = ReadingState::ERROR;
				}
				else
				{
					m_State = ReadingState::SHOWING_OUTPUT;
					
					m_Component.get()->ShowPort(tempStr, std::cout);
				}
				
				break;
			case ReadingState::SHOWING_OUTPUT:
				
				break;
			default:
				WriteError(std::cout, "Something went wrong!");
				break;
			}
		}
	}
}

void FileCommandHandler::WriteError(std::ostream & _o, std::string const & _errStr)
{
	std::cout << "Error: "
		<< _errStr
		<< "\n";
}