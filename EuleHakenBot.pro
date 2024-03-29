QT       += core gui network websockets

INCLUDEPATH += src/

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

TEMPLATE = app

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    src/IrcMessage.cpp \
    src/PrivmsgMessage.cpp \
    src/WebSocket.cpp \
    src/main.cpp

SOURCES += \
    src/Channel.cpp \
    src/Helix.cpp \
    src/NetworkManager.cpp \
    src/NetworkRequest.cpp \
    src/NetworkResult.cpp \
    src/Paths.cpp \
    src/main.cpp

HEADERS += \
    src/Channel.hpp \
    src/Helix.hpp \
    src/NetworkData.hpp \
    src/NetworkManager.hpp \
    src/NetworkRequest.hpp \
    src/NetworkRequestType.hpp \
    src/NetworkResult.hpp \
    src/Paths.hpp \
    src/PostToThread.hpp \
    src/main.cpp

HEADERS += \
    src/IrcMessage.hpp \
    src/MessageHandler.hpp \
    src/PrivmsgMessage.hpp \
    src/PrivmsgMessageHandler.hpp \
    src/WebSocket.hpp

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
