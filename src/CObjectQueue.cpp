#include "CObjectQueue.h"

CObjectQueue::CObjectQueue()
	: LArray(sizeof(void *))
{
}

long CObjectQueue::GetItemCount() {
	return GetCount();
}

void CObjectQueue::AllClear() {
	RemoveItemsAt(GetCount(), index_First);
}

void CObjectQueue::AddItem(void *item) {
	InsertItemsAt(1, index_Last, &item);
}

void CObjectQueue::RemoveItem(long index) {
	RemoveItemsAt(1, index);
}
