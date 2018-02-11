#include "inputportelement.h"

InputPortElement::InputPortElement(const InputPort & _inPort)
	: m_inPort(_inPort)
{
}

bool InputPortElement::Evaluate() const
{
	return m_inPort.getValue();
}