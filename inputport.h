#ifndef _INPUT_PORT_H_
#define _INPUT_PORT_H_

#include "port.h"

class InputPort
	: public Port
{
public:

	InputPort(std::string const & _portName, bool _portState);
	InputPort(std::string const & _portName);

	void SetPortState(bool _state);

	virtual bool getValue() const override;

private:

	bool m_portState = false;
};

inline bool InputPort::getValue() const
{
	return m_portState;
}

#endif