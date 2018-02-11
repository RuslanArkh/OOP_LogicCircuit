#ifndef _INPUT_PORT_ELEMENT_H_
#define _INPUT_PORT_ELEMENT_H_

#include "element.h"
#include "inputport.h"

class InputPortElement
	: public Element
{

public:

	InputPortElement(const InputPort & _inPort);

	bool Evaluate() const override;

	

private:

	const InputPort & m_inPort;

	void addArgument(const Element & _arg) override {}
};

#endif