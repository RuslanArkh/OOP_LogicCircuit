#include "multiargelement.h"

#include <stdexcept>
#include <cassert>

MultiArgElement::MultiArgElement(TypeBinary _type)
	: m_type(_type)
{
}

MultiArgElement::MultiArgElement(TypeBinary _type, const Element * _element)
	: m_type(_type)
{
	m_arguments.push_back(_element);
}

MultiArgElement::MultiArgElement(TypeBinary _type, std::vector< const Element * > const & _elements)
	: m_type(_type)
{
	std::for_each(
			_elements.begin()
			, _elements.end()
			, [this]
			(Element const * tempElem)
			{
				this->m_arguments.push_back(tempElem);
			}
	);
}
/*
BinaryElement::BinaryElement(TypeBinary _type, std::initializer_list< std::shared_ptr<Element> > const & _elements)
	: m_type(_type)
{
	std::for_each(
		_elements.begin()
		, _elements.end()
		, [this]
		(std::shared_ptr<Element> const & tempElem)
		{
			this->m_arguments.push_back(tempElem);
		}
	);
}
*/

bool MultiArgElement::Evaluate() const
{
	bool result;
	switch (m_type)
	{
	case AND:
		result = true;
		std::for_each(
			m_arguments.begin()
			, m_arguments.end()
			, [this, &result]
			(Element const * goElem)
			{
				if (!goElem->Evaluate())
					result = false;
			}
		);
		//return m_argElement1->Evaluate() && m_argElement2->Evaluate();
		break;
	case OR:
		result = false;
		std::for_each(
			m_arguments.begin()
			, m_arguments.end()
			, [this, &result]
			(Element const * goElem)
		{
			if (goElem->Evaluate())
				result = true;
		}
		);
		break;
		//return m_argElement1->Evaluate() || m_argElement2->Evaluate();
	case XOR:
		if (std::count_if(
			m_arguments.begin()
			, m_arguments.end()
			, []
			(Element const * goElem)
			{
				return goElem->Evaluate();
			}
		) % 2 == 0)
			result = false;
		else
			result = true;
		break;
		//return m_argElement1->Evaluate() ^ m_argElement2->Evaluate();
	default:
		assert(0);
	}

	return result;
}

void MultiArgElement::addArgument(const Element & _arg)
{
	m_arguments.push_back(&_arg);
}