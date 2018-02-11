#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "combinationalcircuit.h"

class Component
	: public CombinationalCircuit
{
private:

	void MakeMUX(	std::vector<std::string> const & _inputPortNames,
					std::vector<std::string> const & _outputPortNames);
	void MakeDMX();
	void MakeCH();
	void MakeDCH();

	bool IsValid(int _inputSize, int _outputSize);

public:

	enum ComponentType { MUX, DMX, CH, DCH };

	Component(ComponentType _CompType);
	Component(ComponentType _CompType, 
		std::string const & _inputPortNames, 
		std::string const & _outputPortNames);

	void SetInput(std::string const & _portName, bool _value);

	void ShowPort(std::string const & _portName, std::ostream & _o);

	bool findInPort(std::string const & _portName) const;
	bool findOutPort(std::string const & _portName) const;

	void addV(std::string const & _v, bool _state);
	

private:

	const ComponentType m_CompType;

	int D_inputs, A_controllers, Q_outputs;

	bool V = false;
};

inline bool Component::findInPort(std::string const & _portName) const
{
	return (bool)(this->m_inPorts.find(_portName)->second != nullptr);
}

inline bool Component::findOutPort(std::string const & _portName) const
{
	return (bool)(m_outPorts.find(_portName)->second != nullptr);
}

#endif