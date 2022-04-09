#include "ReflSetWidget.h"
#include "TestReflSet.h"
#include <QtWidgets/QApplication>
#include <QDebug>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);

	/*Test8Set testStructSet;
	Refl8Set refl8Set;
	Ramio::ReflSet reflSet(testStructSet.meta());
	qDebug()<<sizeof(Ramio::ItemData)<<sizeof(Ramio::Item);
	qDebug()<<sizeof(Test8Data)<<sizeof(Test8Item)<<sizeof(Test8Set);
	qDebug()<<sizeof(Ramio::ReflData<8>)<<sizeof(Ramio::ReflItem<8>)<<sizeof(Refl8Set);
	qDebug()<<"sizeof<Ramio::ReflSet>="<<sizeof(reflSet);
	reflSet.createItem();*/

	ReflSetWidget* w = new ReflSetWidget();
	w->show();
	int res = a.exec();
	delete w;
	return res;
}
