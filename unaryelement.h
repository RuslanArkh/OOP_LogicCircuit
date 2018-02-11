#ifndef _UNARY_ELEMENT_H_
#define _UNARY_ELEMENT_H_

#include "element.h"

class UnaryElement
	: public Element
{

public:

	enum TypeUnary { BUFFER, INVERTER };

	UnaryElement(TypeUnary _type, const Element & _element);

	bool Evaluate() const override;

	const TypeUnary & getType() const;

private:

	TypeUnary m_type;

	const Element & m_argElement;

	void addArgument( const Element & _arg) override {}
};

inline const UnaryElement::TypeUnary & UnaryElement::getType() const
{
	return m_type;
}

#endif