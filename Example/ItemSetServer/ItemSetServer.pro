
TARGET = ItemSetServer
TEMPLATE = app

ROOT_DIR = $$PWD/../../

DESTDIR		= $$ROOT_DIR/Bin

DEFINES += TARGET_AUTHOR="\\\"Smithcoder\\\""
DEFINES += TARGET_NAME="\\\"ItemSetServerExample\\\""

INCLUDEPATH		+= $$ROOT_DIR/Source

CONFIG += c++14
QMAKE_CXXFLAGS	+= -Wno-unused-parameter

QT		+= core gui widgets xml sql network

unix {
LIBS += "-L$$ROOT_DIR/Lib" -lRamio
}
win32 {
LIBS += "-L$$ROOT_DIR/Lib" -lRamio0
}

SOURCES += main.cpp \
	MainWidget.cpp \
	ItemSetServer.cpp \
	Tasks.cpp \
	Users.cpp \

HEADERS += \
	MainWidget.h \
	ItemSetServer.h \
	Tasks.h \
	Users.h \
