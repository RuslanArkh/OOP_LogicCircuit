#ifndef _MULTI_ARG_ELEMENT_H_
#define _MULTI_ARG_ELEMENT_H_

#include "element.h"

#include <vector>
#include <initializer_list>
#include <algorithm>

class MultiArgElement
	: public Element
{
public: 

	enum TypeBinary { AND, OR, XOR };

	//BinaryElement(TypeBinary _type, Element const * _element1, Element const * _element2);
	MultiArgElement(TypeBinary _type);
	MultiArgElement(TypeBinary _type, const Element * _element);
	MultiArgElement(TypeBinary _type, std::vector< const Element * > const & _elements);

	const TypeBinary & getType() const;

	bool Evaluate() const override;

	/* virtual */ void addArgument(const Element & _arg) override;
	int countArguments() const;

private:

	const TypeBinary m_type;

	std::vector< const Element * > m_arguments;
};

inline const MultiArgElement::TypeBinary & MultiArgElement::getType() const
{
	return m_type;
}

inline int MultiArgElement::countArguments() const
{
	return m_arguments.size();
}

#endif