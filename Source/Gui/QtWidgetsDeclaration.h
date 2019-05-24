#pragma once

#include <QtWidgets/QWidget>
class QCheckBox;
class QComboBox;
class QDateTimeEdit;
class QGraphicsScene;
class QGraphicsPathItem;
class QLabel;
class QSpinBox;
class QSplitter;
class QStackedWidget;
class QTableView;
class QHBoxLayout;
class QVBoxLayout;



class QTimer;

#define QCOMBOBOX_INDEXCHANGED static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged)
#define QDOUBLESPINBOX_VALUECHANGED static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged)
#define QSPINBOX_VALUECHANGED static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged)
#define QWIDGET_SETFOCUS static_cast<void (QLineEdit::*)()>(&QWidget::setFocus)
