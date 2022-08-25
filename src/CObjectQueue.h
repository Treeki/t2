#pragma once

#include <LArray.h>

class CObjectQueue : public LArray {
public:
	CObjectQueue();

	long GetItemCount();
	void AllClear();
	void AddItem(void *item);
	void RemoveItem(long index);
};
