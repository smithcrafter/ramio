#Network.pro.pri

HEADERS += \
	$$PWD/../Source/Network/NetGlobal.h \
	$$PWD/../Source/Network/TcpServer.h \
	$$PWD/../Source/Network/TcpClient.h \
	$$PWD/../Source/Network/PacketBuilder.h \
	$$PWD/../Source/Network/SslServer.h \
	$$PWD/../Source/Network/SslClient.h \
	$$PWD/../Source/Network/Core/SslTcpServer.h \
	$$PWD/../Source/Network/Core/TcpCoreServer.h \
	$$PWD/../Source/Network/Core/TcpCoreClient.h \


SOURCES += \
	$$PWD/../Source/Network/NetGlobal.cpp \
	$$PWD/../Source/Network/TcpServer.cpp \
	$$PWD/../Source/Network/TcpClient.cpp \
	$$PWD/../Source/Network/PacketBuilder.cpp \
	$$PWD/../Source/Network/SslServer.cpp \
	$$PWD/../Source/Network/SslClient.cpp \
	$$PWD/../Source/Network/Core/SslTcpServer.cpp \
	$$PWD/../Source/Network/Core/TcpCoreServer.cpp \
	$$PWD/../Source/Network/Core/TcpCoreClient.cpp \


