#       MetaItemTest+libRamio
#       Проверка использования айтемов.

TARGET = MetaItemTest
TEMPLATE = app

ROOT_DIR = $$PWD/../../

DESTDIR		 = $$ROOT_DIR/Bin

DEFINES += TARGET_AUTHOR="\\\"Smithcoder\\\""
DEFINES += TARGET_NAME="\\\"MetaItemTest\\\""

INCLUDEPATH			 += $$ROOT_DIR/Include $$ROOT_DIR/Source

CONFIG += c++14
QMAKE_CXXFLAGS  += -Wno-unused-parameter
QT	   += core gui widgets

unix {
LIBS += "-L$$ROOT_DIR/Lib" -lRamio
}
win32 {
LIBS += "-L$$ROOT_DIR/Lib" -lRamio0
}


SOURCES += main.cpp \
	Widget.cpp \
	SuperItem.cpp

HEADERS += \
	Widget.h \
	SuperItem.h

