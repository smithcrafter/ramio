#Ramio.pro.pri

contains(DEFINES, RAMIO_LIB) {
	DEFINES += TARGET_AUTHOR="\\\"Smithcoder\\\""
	DEFINES += TARGET_NAME="\\\"Ramio\\\""
} else {
	DEFINES += RAMIO_DIRECT
}

ROOT_DIR = $$PWD/..
INCLUDEPATH		+= $$ROOT_DIR/Source
INCLUDEPATH		+= $$ROOT_DIR/Include

QMAKE_CXXFLAGS += -std=c++17
QMAKE_CXXFLAGS	+= -Wno-unused-parameter

QT		+= core xml sql network

contains(CONFIG, console) {
	DEFINES += CONSOLE_APP
	QT -= gui
} else {
	QT		+= gui widgets
}

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
	include(Gui.pri)
	include(Models.pri)
	include(Widgets.pri)
}
