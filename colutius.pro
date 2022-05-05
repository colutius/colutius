QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cpp \
    src/irc/fileio.cpp \
    src/irc/server.cpp \
    src/irc/channel.cpp \
    src/irc/message.cpp \
    src/irc/client.cpp\
    src/ui/bochatwidget.cpp \
    src/ui/config.cpp \
    src/ui/login.cpp \
    src/ui/widget.cpp \
    src/ui/systemTrayIcon.cpp \

HEADERS += \
    src/irc/fileio.h \
    src/irc/server.h \
    src/irc/channel.h \
    src/irc/message.h \
    src/irc/client.h \
    src/ui/bochatwidget.h \
    src/ui/config.h \
    src/ui/login.h \
    src/ui/widget.h \
    src/ui/systemTrayIcon.h \

FORMS += \
    src/ui/config.ui \
    src/ui/login.ui \
    src/ui/widget.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/resource.qrc\

DISTFILES += \
    resource/img/logo.rc\

RC_FILE += \
    resource/img/logo.rc\
