#Ramio.pro.pri

contains(DEFINES, RAMIO_LIB) {
	DEFINES += TARGET_AUTHOR="\\\"Smithcoder\\\""
	DEFINES += TARGET_NAME="\\\"Ramio\\\""
} else {
	DEFINES += RAMIO_DIRECT
}

ROOT_DIR = $$PWD/..
INCLUDEPATH		+= $$PWD/../Source
INCLUDEPATH		+= $$PWD/../Include

QMAKE_CXXFLAGS += -std=c++17

QT		+= core xml sql network

contains(CONFIG, console) {
	DEFINES += CONSOLE_APP
	QT -= gui
} else {
	QT		+= gui widgets
}

DEFINES += QT_DEPRECATED_WARNINGS

HEADERS += \
	$$PWD/../Source/ramio.h \

SOURCES += \
	$$PWD/../Source/ramio.cpp \

include(Sets.pri)
include(Items.pri)
include(Log.pri)
include(Database.pri)
include(Global.pri)
include(Network.pri)
include(Protocol.pri)
include(Connection.pri)

contains(QT, gui){
	include(Gui.pri)
	include(Models.pri)
	include(Widgets.pri)
}

android{
	message("RAMIO_ANDROID")
	INCLUDEPATH+=$$PWD/../../3rdparty/zstd-dev/lib/
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/decompress/zstd_decompress.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/decompress/zstd_decompress_block.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/decompress/zstd_ddict.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/compress/zstd_compress.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/common/zstd_common.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/common/xxhash.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/compress/zstd_double_fast.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/compress/zstd_fast.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/compress/zstd_lazy.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/compress/zstd_opt.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/compress/zstd_ldm.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/compress/hist.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/compress/fse_compress.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/common/fse_decompress.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/compress/zstd_compress_sequences.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/decompress/huf_decompress.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/common/entropy_common.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/compress/huf_compress.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/compress/zstd_compress_superblock.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/compress/zstd_compress_literals.c
	SOURCES +=$$PWD/../../3rdparty/zstd-dev/lib/common/error_private.c
}
