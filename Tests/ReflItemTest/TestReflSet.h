#pragma once

#include <Items/MetaItems.h>
#include <Items/ReflItems.h>
#include <Items/MetaStandardItems.h>

struct Test8Data : Ramio::ItemData
{
	quint64 value;
};

using Test8Item = Ramio::StructItem<Test8Data>;

GENERATE_METASET(Test8Set, Test8Item, Test8Data, "Test8s", "Test8");

using Refl8Set = Ramio::ItemSet<Ramio::ReflItem<8>, Ramio::ReflData<8>>;


struct TestData : Ramio::MetaStandardItemData
{
	qint64 value;

	RMETA_DATA_START(Ramio::MetaItemData)
	RMETA_DATA_FIELD_C(value, Long,  "Значение")
	RMETA_DATA_END
};

GENERATE_HEADER_STANDARDCLASS(TestItem, TestData)
GENERATE_HEADER_STANDARDSET(TestSet, TestItem, TestData)

