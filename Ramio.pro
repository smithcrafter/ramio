#Ramio.pro

DEFINES += RAMIO_LIB

TARGET		= Ramio
VERSION		= 0.1.9
TEMPLATE	= lib
DESTDIR		= $$PWD/Lib

include(./SubProjects/Ramio.pri)

DISTFILES += \
	.gitignore \
	LICENSE \
	README.md \
	CHANGELOG.md \

message("DEFINES = " $$DEFINES)

