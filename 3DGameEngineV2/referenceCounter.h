#ifndef REFERENCECOUNTER_H_INCLUDED
#define REFERENCECOUNTER_H_INCLUDED

class ReferenceCounter
{
public:
	ReferenceCounter();
	virtual ~ReferenceCounter();

	void addReference();
	
};

#endif