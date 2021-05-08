#Sets.pro.pri

HEADERS += \
	$$PWD/../Source/Sets/Arg.h \
	$$PWD/../Source/Sets/Config.h \
	$$PWD/../Source/Sets/Settings.h \

SOURCES += \
	$$PWD/../Source/Sets/Arg.cpp \
	$$PWD/../Source/Sets/Config.cpp \
	$$PWD/../Source/Sets/Settings.cpp \

contains(QT, gui){

SOURCES += \
	$$PWD/../Source/Sets/UISets.cpp \

HEADERS += \
	$$PWD/../Source/Sets/UISets.h \

}
