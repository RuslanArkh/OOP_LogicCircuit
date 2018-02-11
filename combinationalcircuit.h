#ifndef _COMBINATIONAL_CIRCUIT_H_
#define _COMBINATIONAL_CIRCUIT_H_

#include "element.h"
#include "port.h"
#include "inputport.h"
#include "outputport.h"

#include <vector>
#include <memory>
#include <initializer_list>
#include <map>
#include <unordered_map>
#include <string>


class CombinationalCircuit
{
public:

	CombinationalCircuit();
	CombinationalCircuit(
		std::vector< std::unique_ptr<Element> > const & _listElements
		, std::vector< InputPort > const & _listInPorts
		, std::vector< OutputPort > const & _listOutPorts
	);

protected:
	//	Functions for inserting elements and ports
	void addElement(std::unique_ptr<Element> _element);
	void addInPort(InputPort const & _inPort);
	void addOutPort(OutputPort const & _outPort);

	//	Vector of logical elements
	std::vector< std::unique_ptr<Element> > m_elements;

	//	Vector of input elements
	std::vector< std::unique_ptr<Element> > m_inElements;

	//	Hash tables for input and output ports
	std::unordered_map<std::string, std::unique_ptr<InputPort> > m_inPorts;
	std::unordered_map<std::string, std::unique_ptr<OutputPort> > m_outPorts;

public:

	bool getOutValueOf(std::string & _portName);

};

#endif