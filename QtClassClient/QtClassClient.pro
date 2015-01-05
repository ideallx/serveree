#-------------------------------------------------
#
# Project created by QtCreator 2014-09-24T12:50:41
#
#-------------------------------------------------

QT       += core gui axcontainer multimedia multimediawidgets concurrent

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TouchPad
TEMPLATE = app

DEFINES += NOMINMAX
DEFINES += WIN32

CONFIG += c++11

SOURCES  += main.cpp\
            LayerUI\mainwindow.cpp \
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
    BizLogic/CGraphicLogic.cpp \
    BizLogic/cfilelogic.cpp \
    BizLogic/cauthlogic.cpp \
    BizLogic/cplayerlogic.cpp \
    player/pptplayer.cpp \
    player/absplayer.cpp \
    player/playerfactory.cpp \
    player/docplayer.cpp \
    player/jpgplayer.cpp \
    player/videoplayer.cpp \
    LayerUI/DrawingScreen/cshape.cpp \
    LayerUI/DrawingScreen/myscene.cpp \
    LayerUI/MsgGenerator/cfilemsggenerator.cpp \
    LayerUI/MsgGenerator/cgraphicmsgcreator.cpp \
    LayerUI/MsgGenerator/cplayergenerator.cpp \
    LayerUI/UserInterface/cloginbutton.cpp \
    LayerUI/UserInterface/colorcombox.cpp \
    LayerUI/UserInterface/cpromptframe.cpp \
    LayerUI/UserInterface/csettingsbutton.cpp \
    LayerUI/UserInterface/cshapechooser.cpp \
    LayerUI/UserInterface/linewidthcombox.cpp \
    LayerUI/UserInterface/prompt.cpp \
    LayerUI/UserInterface/widgetwarelistitem.cpp \
    LayerUI/UserInterface/myview.cpp \
    LayerUI/UserInterface/cuserlistwidget.cpp \
    LayerUI/SlideScreen/coursewarewidget.cpp \
    Reliable/Strategy/CSettings.cpp \
    BeforeClass/logindialog.cpp \
    BeforeClass/totalprocess.cpp \
    BizLogic/cloadlogic.cpp \
    LayerUI/MsgGenerator/cracegenerator.cpp \
    LayerUI/UserInterface/dialogpixmap.cpp \
    BizLogic/datasingleton.cpp \
    Net/replays.cpp \
    BeforeClass/dialogchoosereplay.cpp \
    LayerUI/UserInterface/dialogchooseshape.cpp \
    BizLogic/CQuestionLogic.cpp \
    LayerUI/UserInterface/dialogbuildquestion.cpp \
    LayerUI/UserInterface/dialoganswerquestion.cpp \
    LayerUI/UserInterface/dialogbuildstatistics.cpp

HEADERS  += LayerUI\mainwindow.h \
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
    Message/CModuleAgent.h \
    stdafx.h \
    BizLogic/CBusinessLogic.h \
    BizLogic/CGraphicLogic.h \
    BizLogic/cfilelogic.h \
    BizLogic/cauthlogic.h \
    BizLogic/cplayerlogic.h \
    player/pptplayer.h \
    player/absplayer.h \
    player/playerfactory.h \
    player/docplayer.h \
    player/jpgplayer.h \
    player/videoplayer.h \
    LayerUI/DrawingScreen/cshape.h \
    LayerUI/DrawingScreen/myscene.h \
    LayerUI/MsgGenerator/cfilemsggenerator.h \
    LayerUI/MsgGenerator/cgraphicmsgcreator.h \
    LayerUI/MsgGenerator/cplayergenerator.h \
    LayerUI/UserInterface/cloginbutton.h \
    LayerUI/UserInterface/colorcombox.h \
    LayerUI/UserInterface/cpromptframe.h \
    LayerUI/UserInterface/csettingsbutton.h \
    LayerUI/UserInterface/cshapechooser.h \
    LayerUI/UserInterface/cuserlistwidget.h \
    LayerUI/UserInterface/linewidthcombox.h \
    LayerUI/UserInterface/prompt.h \
    LayerUI/UserInterface/widgetwarelistitem.h \
    LayerUI/UserInterface/myview.h \
    LayerUI/SlideScreen/coursewarewidget.h \
    Reliable/Strategy/CSettings.h \
    BeforeClass/logindialog.h \
    BeforeClass/totalprocess.h \
    BizLogic/cloadlogic.h \
    LayerUI/MsgGenerator/cracegenerator.h \
    LayerUI/UserInterface/dialogpixmap.h \
    BizLogic/datasingleton.h \
    Net/replays.h \
    BeforeClass/dialogchoosereplay.h \
    LayerUI/UserInterface/dialogchooseshape.h \
    BizLogic/CQuestionLogic.h \
    LayerUI/UserInterface/dialogbuildquestion.h \
    LayerUI/UserInterface/dialoganswerquestion.h \
    LayerUI/UserInterface/dialogbuildstatistics.h

FORMS    += \
    loginwidget.ui \
    settingwidget.ui \
    prompt.ui \
    widgetwarelistitem.ui \
    coursewarewidget.ui \
    mainwindow.ui \
    BeforeClass/logindialog.ui \
    LayerUI/UserInterface/dialogpixmap.ui \
    BeforeClass/dialogchoosereplay.ui \
    LayerUI/UserInterface/dialogchooseshape.ui \
    LayerUI/UserInterface/dialogbuildquestion.ui \
    LayerUI/UserInterface/dialoganswerquestion.ui \
    LayerUI/UserInterface/dialogbuildstatistics.ui

INCLUDEPATH += .
INCLUDEPATH += include
INCLUDEPATH += LayerUI/UserInterface
INCLUDEPATH += LayerUI/SlideScreen
INCLUDEPATH += Reliable/OSInedependent/libiop

OTHER_FILES += \
    Reliable/Zip/zdll.lib \
    Reliable/Zip/zlib.lib \
    Reliable/Zip/zlib1.dll

RESOURCES += \
    ui.qrc

RC_ICONS = class.ico
