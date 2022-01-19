// for test

#pragma once

#include "Item.h"
#include "StructItem.h"

namespace Ramio {

template<int COUNT>
struct ReflData : public ItemData
{
	char dsubtata[COUNT] ;
};

template<int COUNT>
class ReflItem : public StructItem<ReflData<COUNT>>
{
	typedef ReflData<COUNT> Data;
	typedef StructItem<ReflData<COUNT>> Base;

	ReflItem() : Base() {}
	ReflItem(const Data& data) : Base(data) {}
};

} // Ramio::
