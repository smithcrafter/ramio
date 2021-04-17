#Connection.pro.pri

HEADERS += \
	$$PWD/../Source/Connection/Connection.h \
	$$ROOT_DIR/Source/Connection/TcpServerHandler.h \
	$$ROOT_DIR/Source/Connection/ConnectionHandler.h \
	$$ROOT_DIR/Source/Connection/TcpClientHandler.h



SOURCES += \
	$$PWD/../Source/Connection/Connection.cpp \
	$$ROOT_DIR/Source/Connection/TcpServerHandler.cpp \
	$$ROOT_DIR/Source/Connection/ConnectionHandler.cpp \
	$$ROOT_DIR/Source/Connection/TcpClientHandler.cpp

