#include "outputport.h"

OutputPort::OutputPort(std::string const & _portName, const Element & _element)
	: Port(_portName)
	, m_element(_element)
{
}

void OutputPort::BindElement(const Element & _element)
{
}

bool OutputPort::getValue() const
{
	return m_element.Evaluate();
}