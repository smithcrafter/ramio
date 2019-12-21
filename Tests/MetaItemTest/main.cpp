#include <QApplication>
#include <QTest>
#include "SuperItemTest.h"

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QScopedPointer sit(new SuperItemTest(&a));
	QTest::qExec(sit.data(), argc, argv);
	sit->printSizes();
	sit->printValueToString();
	return 0;
}
