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
    Reliable/OSInedependent/pthread/cleanup.c \
    Reliable/OSInedependent/pthread/global.c \
    Reliable/OSInedependent/pthread/pthread_cancel.c \
    Reliable/OSInedependent/pthread/pthread_create.c \
    Reliable/OSInedependent/pthread/pthread_detach.c \
    Reliable/OSInedependent/pthread/pthread_equal.c \
    Reliable/OSInedependent/pthread/pthread_getspecific.c \
    Reliable/OSInedependent/pthread/pthread_key_create.c \
    Reliable/OSInedependent/pthread/pthread_key_delete.c \
    Reliable/OSInedependent/pthread/pthread_kill.c \
    Reliable/OSInedependent/pthread/pthread_mutex_consistent.c \
    Reliable/OSInedependent/pthread/pthread_mutex_destroy.c \
    Reliable/OSInedependent/pthread/pthread_mutex_init.c \
    Reliable/OSInedependent/pthread/pthread_mutex_lock.c \
    Reliable/OSInedependent/pthread/pthread_mutex_trylock.c \
    Reliable/OSInedependent/pthread/pthread_mutex_unlock.c \
    Reliable/OSInedependent/pthread/pthread_mutexattr_destroy.c \
    Reliable/OSInedependent/pthread/pthread_self.c \
    Reliable/OSInedependent/pthread/pthread_setschedparam.c \
    Reliable/OSInedependent/pthread/pthread_setspecific.c \
    Reliable/OSInedependent/pthread/pthread_testcancel.c \
    Reliable/OSInedependent/pthread/pthread_win32_attach_detach_np.c \
    Reliable/OSInedependent/pthread/ptw32_callUserDestroyRoutines.c \
    Reliable/OSInedependent/pthread/ptw32_MCS_lock.c \
    Reliable/OSInedependent/pthread/ptw32_mutex_check_need_init.c \
    Reliable/OSInedependent/pthread/ptw32_new.c \
    Reliable/OSInedependent/pthread/ptw32_processInitialize.c \
    Reliable/OSInedependent/pthread/ptw32_processTerminate.c \
    Reliable/OSInedependent/pthread/ptw32_reuse.c \
    Reliable/OSInedependent/pthread/ptw32_threadDestroy.c \
    Reliable/OSInedependent/pthread/ptw32_threadStart.c \
    Reliable/OSInedependent/pthread/ptw32_throw.c \
    Reliable/OSInedependent/pthread/ptw32_tkAssocCreate.c \
    Reliable/OSInedependent/pthread/ptw32_tkAssocDestroy.c \
    Reliable/OSInedependent/pthread/sched_get_priority_max.c \
    Reliable/OSInedependent/pthread/sched_get_priority_min.c \
    Reliable/OSInedependent/pthread/sched_yield.c \
    Reliable/OSInedependent/pthread/sem_destroy.c \
    Reliable/OSInedependent/pthread/sem_init.c \
    Reliable/OSInedependent/pthread/sem_post.c \
    Reliable/OSInedependent/pthread/sem_wait.c \
    Reliable/OSInedependent/pthread/w32_CancelableWait.c \
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
    LayerUI/colorcombox.cpp \
    LayerUI/linewidthcombox.cpp \
    LayerUI/IpAddressWidget.cpp \
    LayerUI/qeclass.cpp

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
    Reliable/OSInedependent/pthread/config.h \
    Reliable/OSInedependent/pthread/context.h \
    Reliable/OSInedependent/pthread/implement.h \
    Reliable/OSInedependent/pthread/pthread.h \
    Reliable/OSInedependent/pthread/sched.h \
    Reliable/OSInedependent/pthread/semaphore.h \
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
    LayerUI/colorcombox.h \
    LayerUI/linewidthcombox.h \
    LayerUI/IpAddressWidget.h \
    LayerUI/qeclass.h

FORMS    += mainwindow.ui \
    qeclass.ui

INCLUDEPATH += .
INCLUDEPATH += include
INCLUDEPATH += LayerUI
INCLUDEPATH += BizLogic
INCLUDEPATH += Message
INCLUDEPATH += Net

INCLUDEPATH += Reliable/Zip
INCLUDEPATH += Reliable/DataUnit
INCLUDEPATH += Reliable/OSInedependent/pthread
INCLUDEPATH += Reliable/OSInedependent/libiop

OTHER_FILES += \
    Reliable/Zip/zdll.lib \
    Reliable/Zip/zlib.lib \
    Reliable/Zip/zlib1.dll

RESOURCES += \
    application.qrc
