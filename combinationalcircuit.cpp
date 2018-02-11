#include "combinationalcircuit.h"

CombinationalCircuit::CombinationalCircuit()
{
}

CombinationalCircuit::CombinationalCircuit(
	std::vector< std::unique_ptr<Element> > const & _listElements
	, std::vector< InputPort > const & _listInPorts
	, std::vector< OutputPort > const & _listOutPorts)
{
	
	//for (std::unique_ptr<Element> const & x : _listElements)
		//m_elements.push_back(std::move(x));
	for (InputPort y : _listInPorts)
		addInPort(y);
	for (OutputPort z : _listOutPorts)
		addOutPort(z);
		
}

void CombinationalCircuit::addElement(std::unique_ptr<Element> _element)
{
	//m_elements.push_back(std::move(_element));
}

void CombinationalCircuit::addInPort(InputPort const & _inPort)
{
	m_inPorts[_inPort.getName()] = std::make_unique<InputPort>(_inPort);
}

void CombinationalCircuit::addOutPort(OutputPort const & _outPort)
{
	m_outPorts[_outPort.getName()] = std::make_unique<OutputPort>(_outPort);
}

bool CombinationalCircuit::getOutValueOf(std::string & _portName)
{
	return m_outPorts.find(_portName)->second.get()->getValue();
}