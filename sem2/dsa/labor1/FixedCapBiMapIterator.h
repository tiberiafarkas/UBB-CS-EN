#pragma once
#include "FixedCapBiMap.h"
class FixedCapBiMapIterator
{
	//DO NOT CHANGE THIS PART
	friend class FixedCapBiMap;
private:
	FixedCapBiMap& map;
	//TODO - Representation
	int currentPos;

	FixedCapBiMapIterator(FixedCapBiMap& m);
public:
	void first();
	void next();
	TElem removeCurrent();
	TElem getCurrent();
	bool valid() const;
};


