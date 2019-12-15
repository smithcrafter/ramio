#include "Widget.h"
#include <QApplication>
#include <QTest>
#include <SuperItemTest.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	//Widget w;
	//w.show();
	//return a.exec();
	QScopedPointer sit(new SuperItemTest(&a));
	sit->printSizes();
	sit->printValueToString();
	QTest::qExec(sit.data(), argc, argv);
	return 0;
}
