#ifndef _OUTPUT_PORT_H_
#define _OUTPUT_PORT_H_

#include "port.h"
#include "element.h"

#include <cassert>

class OutputPort
	: public Port
{

public:


	OutputPort(std::string const & _portName, const Element & _element);

	void BindElement(const Element & _element);

	virtual bool getValue() const override;

private:

	const Element & m_element;

};

#endif