#include "unaryelement.h"

UnaryElement::UnaryElement(TypeUnary _type, const Element & _element)
	: m_type(_type), 
	m_argElement(_element)
{
}

bool UnaryElement::Evaluate() const
{
	if (m_type == TypeUnary::BUFFER)
		return m_argElement.Evaluate();
	else
		return !m_argElement.Evaluate();
}