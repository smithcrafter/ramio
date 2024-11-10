#Ramio.pro

DEFINES += RAMIO_LIB

TARGET		= Ramio-core
VERSION		= 0.1.8
TEMPLATE	= lib
DESTDIR		= $$PWD/Lib

CONFIG+=console

include(./SubProjects/Ramio.pri)

DISTFILES += \
	.gitignore \
	LICENSE \
	README.md \
	CHANGELOG.md \

message("DEFINES = " $$DEFINES)

