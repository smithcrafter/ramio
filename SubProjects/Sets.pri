#Sets.pro.pri

HEADERS += \
	$$ROOT_DIR/Source/Sets/Arg.h \
	$$ROOT_DIR/Source/Sets/Config.h \
	$$ROOT_DIR/Source/Sets/Settings.h \

SOURCES += \
	$$ROOT_DIR/Source/Sets/Arg.cpp \
	$$ROOT_DIR/Source/Sets/Config.cpp \
	$$ROOT_DIR/Source/Sets/Settings.cpp \

contains(QT, gui){

SOURCES += \
	$$ROOT_DIR/Source/Sets/UISets.cpp \

HEADERS += \
	$$ROOT_DIR/Source/Sets/UISets.h \

}
