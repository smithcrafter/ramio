#Ramio.pro.pri

contains(DEFINES, RAMIO_LIB) {
	DEFINES += TARGET_AUTHOR="\\\"Smithcoder\\\""
	DEFINES += TARGET_NAME="\\\"Ramio\\\""
}
else
{
	DEFINES += RAMIO_DIRECT
}

ROOT_DIR = $$PWD/..
INCLUDEPATH		+= $$ROOT_DIR/Source

QMAKE_CXXFLAGS += -std=c++14
QMAKE_CXXFLAGS	+= -Wno-unused-parameter

QT		+= core gui widgets xml sql network

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
	$$ROOT_DIR/Source/ramio.h \

SOURCES += \
	$$ROOT_DIR/Source/ramio.cpp \


include(Sets.pri)
include(Items.pri)
include(Log.pri)
include(Database.pri)
include(Global.pri)
include(Network.pri)
include(Protocol.pri)

contains(QT, gui){
	include(Models.pri)
	include(ItemWidgets.pri)
	include(Widgets.pri)
	include(Gui.pri)
}
