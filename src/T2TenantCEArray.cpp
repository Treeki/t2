#include "T2TenantCEArray.h"

T2TenantCEArray::T2TenantCEArray() {
}

T2TenantCEArray::~T2TenantCEArray() {
}

UInt16 T2TenantCEArray::GetFloorID(Int32 index) {
	UInt16 id;
	if (FetchItemAt(index, &id))
		return id;
	else
		return 0;
}

void T2TenantCEArray::SetFloorID(UInt16 id) {
	InsertItemsAt(1, index_Last, &id);
}

FourCharCode T2TenantCEArray::GetCEClassID() {
	return 'TCEA';
}
