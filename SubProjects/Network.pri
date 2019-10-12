#Network.pro.pri

HEADERS += \
	$$ROOT_DIR/Source/Network/NetGlobal.h \
	$$ROOT_DIR/Source/Network/TcpServer.h \
	$$ROOT_DIR/Source/Network/TcpClient.h \
	$$ROOT_DIR/Source/Network/PacketBuilder.h \
	$$ROOT_DIR/Source/Network/SslServer.h \
	$$ROOT_DIR/Source/Network/SslClient.h \
	$$ROOT_DIR/Source/Network/Core/SslTcpServer.h \
	$$ROOT_DIR/Source/Network/Core/TcpCoreServer.h \
	$$ROOT_DIR/Source/Network/Core/TcpCoreClient.h \

SOURCES += \
	$$ROOT_DIR/Source/Network/NetGlobal.cpp \
	$$ROOT_DIR/Source/Network/TcpServer.cpp \
	$$ROOT_DIR/Source/Network/TcpClient.cpp \
	$$ROOT_DIR/Source/Network/PacketBuilder.cpp \
	$$ROOT_DIR/Source/Network/SslServer.cpp \
	$$ROOT_DIR/Source/Network/SslClient.cpp \
	$$ROOT_DIR/Source/Network/Core/SslTcpServer.cpp \
	$$ROOT_DIR/Source/Network/Core/TcpCoreServer.cpp \
	$$ROOT_DIR/Source/Network/Core/TcpCoreClient.cpp \


