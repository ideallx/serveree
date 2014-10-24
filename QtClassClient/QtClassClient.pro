#-------------------------------------------------
#
# Project created by QtCreator 2014-09-24T12:50:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TouchPad
TEMPLATE = app

CONFIG += c++11

SOURCES  += main.cpp\
            LayerUI\mainwindow.cpp \
            LayerUI\myscene.cpp \
            LayerUI\myview.cpp \
    BizLogic/CBaseLogic.cpp \
    BizLogic/CUserLogic.cpp \
    Net/CClientNet.cpp \
    Reliable/Connections/CAbsConnection.cpp \
    Reliable/Connections/CAbsSocket.cpp \
    Reliable/Connections/CConnection.cpp \
    Reliable/Connections/CHubConnection.cpp \
    Reliable/Connections/CPeerConnection.cpp \
    Reliable/Connections/CReliableConnection.cpp \
    Reliable/Connections/CSynSocket.cpp \
    Reliable/DataUnit/CBlock.cpp \
    Reliable/DataUnit/CBlockManager.cpp \
    Reliable/DataUnit/CMessage.cpp \
    Reliable/DataUnit/CPackage.cpp \
    Reliable/OSInedependent/others.cpp \
    Reliable/OSInedependent/libiop/iop_thread.c \
    Reliable/OSInedependent/libiop/iop_util.c \
    Reliable/Server/CAbsServer.cpp \
    Reliable/Server/CAgentServer.cpp \
    Reliable/Server/CServer.cpp \
    Reliable/Server/CWSServer.cpp \
    Reliable/Strategy/CAbsStrategy.cpp \
    Reliable/Strategy/CDestroyStrategy.cpp \
    Reliable/Strategy/CWriteFileStrategy.cpp \
    Reliable/Zip/myzip.cpp \
    Reliable/Zip/ioapi.c \
    Reliable/Zip/iowin32.c \
    Reliable/Zip/unzip.c \
    Reliable/Zip/zip.c \
    Message/CMsgObject.cpp \
    Message/CMsgReceiver.cpp \
    Message/CMsgSender.cpp \
    Message/CModuleAgent.cpp \
    BizLogic/CBusinessLogic.cpp \
    LayerUI/cgraphicmsgcreator.cpp \
    BizLogic/CGraphicLogic.cpp \
    cshape.cpp \
    UserInterface/cloginbutton.cpp \
    UserInterface/csettingsbutton.cpp \
    UserInterface/cuserlistwidget.cpp \
    UserInterface/linewidthcombox.cpp \
    UserInterface/cshapechooser.cpp \
    UserInterface/colorcombox.cpp

HEADERS  += LayerUI\mainwindow.h \
            LayerUI\myscene.h \
            LayerUI\myview.h \
    BizLogic/CBaseLogic.h \
    BizLogic/CUserLogic.h \
    Net/CClientNet.h \
    Reliable/Connections/CAbsConnection.h \
    Reliable/Connections/CAbsSocket.h \
    Reliable/Connections/CConnection.h \
    Reliable/Connections/CHubConnection.h \
    Reliable/Connections/CPeerConnection.h \
    Reliable/Connections/CReliableConnection.h \
    Reliable/Connections/CSynSocket.h \
    Reliable/DataStructure/Pool.h \
    Reliable/DataStructure/TSQueue.h \
    Reliable/DataUnit/CBlock.h \
    Reliable/DataUnit/CBlockManager.h \
    Reliable/DataUnit/CMessage.h \
    Reliable/DataUnit/CPackage.h \
    Reliable/DataUnit/CPeerPacket.h \
    Reliable/DataUnit/UserBase.h \
    Reliable/OSInedependent/others.h \
    Reliable/OSInedependent/libiop/iop_config.h \
    Reliable/OSInedependent/libiop/iop_thread.h \
    Reliable/OSInedependent/libiop/iop_util.h \
    Reliable/Server/CAbsServer.h \
    Reliable/Server/CAgentServer.h \
    Reliable/Server/CServer.h \
    Reliable/Server/CWSServer.h \
    Reliable/Strategy/CAbsStrategy.h \
    Reliable/Strategy/CDestroyStrategy.h \
    Reliable/Strategy/CWriteFileStrategy.h \
    Reliable/Zip/crypt.h \
    Reliable/Zip/ioapi.h \
    Reliable/Zip/iowin32.h \
    Reliable/Zip/myzip.h \
    Reliable/Zip/unzip.h \
    Reliable/Zip/zconf.h \
    Reliable/Zip/zip.h \
    Reliable/Zip/zlib.h \
    Message/CMsgObject.h \
    Message/CMsgReceiver.h \
    Message/CMsgSender.h \
    stdafx.h \
    Message/CModuleAgent.h \
    BizLogic/CBusinessLogic.h \
    LayerUI/cgraphicmsgcreator.h \
    BizLogic/CGraphicLogic.h \
    cshape.h \
    UserInterface/cloginbutton.h \
    UserInterface/csettingsbutton.h \
    UserInterface/cuserlistwidget.h \
    UserInterface/linewidthcombox.h \
    UserInterface/cshapechooser.h \
    UserInterface/colorcombox.h

FORMS    += \
    loginwidget.ui \
    mainwindow.ui \
    settingwidget.ui

INCLUDEPATH += .
INCLUDEPATH += include
INCLUDEPATH += LayerUI
INCLUDEPATH += BizLogic
INCLUDEPATH += Message
INCLUDEPATH += Net
INCLUDEPATH += UserInterface
INCLUDEPATH += Reliable/Zip
INCLUDEPATH += Reliable/DataUnit
INCLUDEPATH += Reliable/OSInedependent/pthread
INCLUDEPATH += Reliable/OSInedependent/libiop

OTHER_FILES += \
    Reliable/Zip/zdll.lib \
    Reliable/Zip/zlib.lib \
    Reliable/Zip/zlib1.dll

RESOURCES += \
    ui.qrc
