#include "inputport.h"

InputPort::InputPort(std::string const & _portName, bool _portState)
	: Port(_portName)
	, m_portState(_portState)
{
}

InputPort::InputPort(std::string const & _portName)
	: Port(_portName)
{
}

void InputPort::SetPortState(bool _state)
{
	m_portState = _state;
}