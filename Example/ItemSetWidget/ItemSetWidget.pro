#	ItemSetWidget+libRamio
#	Пример использования айтемов.

TARGET			= ItemSetWidget
TEMPLATE		= app

ROOT_DIR = $$PWD/../../

DESTDIR		= $$ROOT_DIR/Bin

DEFINES += TARGET_AUTHOR="\\\"Smithcoder\\\""
DEFINES += TARGET_NAME="\\\"ItemSetWidgetExample\\\""

INCLUDEPATH		+= $$ROOT_DIR/Source

CONFIG += c++14
QMAKE_CXXFLAGS	+= -Wno-unused-parameter

QT		+= core gui widgets xml

unix {
LIBS += "-L$$ROOT_DIR/Lib" -lRamio
}
win32 {
LIBS += "-L$$ROOT_DIR/Lib" -lRamio0
}


SOURCES += main.cpp \
	Notes.cpp \
	Sections.cpp \
	ItemSetWidget.cpp \

HEADERS += \
	Notes.h \
	Sections.h \
	ItemSetWidget.h \

