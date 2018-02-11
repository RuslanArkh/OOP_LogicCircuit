#ifndef _PORT_H_
#define _PORT_H_

#include <string>

class Port
{
public:

	Port(std::string const & _name) : m_portName(_name) {}

	virtual bool getValue() const { return false; }

	const std::string & getName() const;

private:

	 std::string m_portName;

};

inline const std::string & Port::getName() const
{
	return m_portName;
}

#endif