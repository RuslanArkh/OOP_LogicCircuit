#ifndef _ELEMENT_H_
#define _ELEMENT_H_

class Element
{
public:

	virtual ~Element() = default;

	virtual bool Evaluate() const = 0;

	virtual void addArgument(const Element & _arg) = 0;
};

#endif