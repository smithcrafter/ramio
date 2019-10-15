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
	QTest::qExec(new SuperItemTest(&a), argc, argv);
	return 0;
}
