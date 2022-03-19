#pragma once

#include <QtWidgets/QWidget>
#include "TestReflSet.h"
class QTabWidget;

class ReflSetWidget : public QWidget
{
public:
	ReflSetWidget(QWidget* parent = Q_NULLPTR);

	void addRandom();

private:
	QTabWidget* tabs_;
	TestSet set;
	Ramio::ReflSet rset;
};
