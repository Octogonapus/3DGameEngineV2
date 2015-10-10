#ifndef REFERENCECOUNTER_H_INCLUDED
#define REFERENCECOUNTER_H_INCLUDED

class ReferenceCounter
{
public:
	ReferenceCounter():
		m_refCount(1) {}

	inline void addReference() { m_refCount++; }
	inline bool removeReference() { m_refCount--; return m_refCount == 0; }

	inline int getReferenceCount() { return m_refCount; }

private:
	int m_refCount;
};

#endif