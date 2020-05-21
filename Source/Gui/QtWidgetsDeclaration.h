#pragma once

#include <Global/QtCoreDeclaration.h>
#include <QtWidgets/QWidget>
#include <QtCore/QPointer>
class QCheckBox;
class QComboBox;
class QDateTimeEdit;
class QDoubleSpinBox;
class QGraphicsScene;
class QGraphicsPathItem;
class QLabel;
class QLineEdit;
class QSpinBox;
class QSplitter;
class QStackedWidget;
class QTabWidget;
class QTableView;
class QTextEdit;
class QHBoxLayout;
class QVBoxLayout;
class QGridLayout;
class QPushButton;
class QToolButton;

#define QCOMBOBOX_INDEXCHANGED static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged)
#define QDOUBLESPINBOX_VALUECHANGED static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)
#define QSPINBOX_VALUECHANGED static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged)
#define QWIDGET_SETFOCUS static_cast<void (QLineEdit::*)()>(&QWidget::setFocus)
