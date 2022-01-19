
#include <Items/MetaItems.h>
#include <Items/ReflItems.h>
#include <QDebug>

struct Test8Data : Ramio::ItemData
{
	quint64 value;
};

using Test8Item = Ramio::StructItem<Test8Data>;

GENERATE_METASET(Test8Set, Test8Item, Test8Data, "Test8s", "Test8");

using ReflSet = Ramio::ItemSet<Ramio::ReflItem<8>, Ramio::ReflData<8>>;


int main(int argc, char *argv[])
{
	qDebug()<<sizeof(Ramio::ItemData)<<sizeof(Ramio::Item);
	qDebug()<<sizeof(Test8Data)<<sizeof(Test8Item)<<sizeof(Test8Set);
	qDebug()<<sizeof(Ramio::ReflData<8>)<<sizeof(Ramio::ReflItem<8>)<<sizeof(ReflSet);

	Test8Set testStructSet;
	ReflSet reflSet;

	return 0;
}
