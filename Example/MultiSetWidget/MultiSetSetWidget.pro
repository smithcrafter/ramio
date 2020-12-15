#	MultiSetWidget+libRamio
#	Пример использования наборов.

TARGET			= MultiSetWidget
TEMPLATE		= app

ROOT_DIR = $$PWD/../../

DESTDIR		= $$ROOT_DIR/Bin

DEFINES += TARGET_AUTHOR="\\\"Smithcoder\\\""
DEFINES += TARGET_NAME="\\\"MultiSetWidgetExample\\\""

INCLUDEPATH		+= $$ROOT_DIR/Include $$ROOT_DIR/Source ../ItemSetWidget/

CONFIG += c++17
QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS	+= -Wno-unused-parameter

QT		+= core gui widgets xml

unix {
LIBS += "-L$$ROOT_DIR/Lib" -lRamio
}
win32 {
LIBS += "-L$$ROOT_DIR/Lib" -lRamio0
}


SOURCES += main.cpp \
	TestItem.cpp \
	MultiSetWidget.cpp \

HEADERS += \
	TestItem.h \
	MultiSetWidget.h \

