#-------------------------------------------------
#
# Project created by QtCreator 2014-10-20T13:55:54
#
#-------------------------------------------------

QT       += widgets testlib

TARGET = tst_qtclassunittesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    ../QtClassClient/UserInterface/cloginbutton.cpp \
    ../QtClassClient/UserInterface/colorcombox.cpp \
    ../QtClassClient/UserInterface/csettingsbutton.cpp \
    ../QtClassClient/UserInterface/cshapechooser.cpp \
    ../QtClassClient/UserInterface/cuserlistwidget.cpp \
    ../QtClassClient/UserInterface/linewidthcombox.cpp \
    ../QtClassClient/BizLogic/CBaseLogic.cpp \
    ../QtClassClient/BizLogic/CBusinessLogic.cpp \
    ../QtClassClient/BizLogic/CGraphicLogic.cpp \
    ../QtClassClient/BizLogic/CUserLogic.cpp \
    ../QtClassClient/LayerUI/cgraphicmsgcreator.cpp \
    ../QtClassClient/LayerUI/colorcombox.cpp \
    ../QtClassClient/LayerUI/IpAddressWidget.cpp \
    ../QtClassClient/LayerUI/linewidthcombox.cpp \
    ../QtClassClient/LayerUI/mainwindow.cpp \
    ../QtClassClient/LayerUI/myscene.cpp \
    ../QtClassClient/LayerUI/myview.cpp \
    ../QtClassClient/Message/CModuleAgent.cpp \
    ../QtClassClient/Message/CMsgObject.cpp \
    ../QtClassClient/Message/CMsgReceiver.cpp \
    ../QtClassClient/Message/CMsgSender.cpp \
    ../QtClassClient/Net/CClientNet.cpp \
    ../QtClassClient/Reliable/Connections/CAbsConnection.cpp \
    ../QtClassClient/Reliable/Connections/CAbsSocket.cpp \
    ../QtClassClient/Reliable/Connections/CConnection.cpp \
    ../QtClassClient/Reliable/Connections/CHubConnection.cpp \
    ../QtClassClient/Reliable/Connections/CPeerConnection.cpp \
    ../QtClassClient/Reliable/Connections/CReliableConnection.cpp \
    ../QtClassClient/Reliable/Connections/CSynSocket.cpp \
    ../QtClassClient/GeneratedFiles/qrc_ui.cpp \
    ../QtClassClient/Reliable/DataUnit/CBlock.cpp \
    ../QtClassClient/Reliable/DataUnit/CBlockManager.cpp \
    ../QtClassClient/Reliable/DataUnit/CMessage.cpp \
    ../QtClassClient/Reliable/DataUnit/CPackage.cpp \
    ../QtClassClient/Reliable/OSInedependent/others.cpp \
    ../QtClassClient/Reliable/Server/CAbsServer.cpp \
    ../QtClassClient/Reliable/Server/CAgentServer.cpp \
    ../QtClassClient/Reliable/Server/CServer.cpp \
    ../QtClassClient/Reliable/Server/CWSServer.cpp \
    ../QtClassClient/Reliable/Strategy/CAbsStrategy.cpp \
    ../QtClassClient/Reliable/Strategy/CDestroyStrategy.cpp \
    ../QtClassClient/Reliable/Strategy/CWriteFileStrategy.cpp \
    ../QtClassClient/Reliable/Zip/myzip.cpp \
    ../QtClassClient/cshape.cpp \
    ../QtClassClient/Reliable/OSInedependent/libiop/iop_thread.c \
    ../QtClassClient/Reliable/OSInedependent/libiop/iop_util.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/cleanup.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/global.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_cancel.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_create.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_detach.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_equal.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_getspecific.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_key_create.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_key_delete.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_kill.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_mutex_consistent.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_mutex_destroy.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_mutex_init.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_mutex_lock.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_mutex_trylock.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_mutex_unlock.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_mutexattr_destroy.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_self.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_setschedparam.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_setspecific.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_testcancel.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread_win32_attach_detach_np.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/ptw32_callUserDestroyRoutines.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/ptw32_MCS_lock.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/ptw32_mutex_check_need_init.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/ptw32_new.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/ptw32_processInitialize.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/ptw32_processTerminate.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/ptw32_reuse.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/ptw32_threadDestroy.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/ptw32_threadStart.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/ptw32_throw.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/ptw32_tkAssocCreate.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/ptw32_tkAssocDestroy.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/sched_get_priority_max.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/sched_get_priority_min.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/sched_yield.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/sem_destroy.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/sem_init.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/sem_post.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/sem_wait.c \
    ../QtClassClient/Reliable/OSInedependent/pthread/w32_CancelableWait.c \
    ../QtClassClient/Reliable/Zip/ioapi.c \
    ../QtClassClient/Reliable/Zip/iowin32.c \
    ../QtClassClient/Reliable/Zip/unzip.c \
    ../QtClassClient/Reliable/Zip/zip.c \
    main.cpp \
    UnitTest/tst_cblock.cpp \
    UnitTest/tst_cblockmanager.cpp \
    UnitTest/tst_CPackage.cpp \
    UnitTest/tst_reliable.cpp \
    common.cpp \
    UnitTest/tst_cagentserver.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../QtClassClient/UserInterface/cloginbutton.h \
    ../QtClassClient/UserInterface/colorcombox.h \
    ../QtClassClient/UserInterface/csettingsbutton.h \
    ../QtClassClient/UserInterface/cshapechooser.h \
    ../QtClassClient/UserInterface/cuserlistwidget.h \
    ../QtClassClient/UserInterface/linewidthcombox.h \
    ../QtClassClient/BizLogic/CBaseLogic.h \
    ../QtClassClient/BizLogic/CBusinessLogic.h \
    ../QtClassClient/BizLogic/CGraphicLogic.h \
    ../QtClassClient/BizLogic/CUserLogic.h \
    ../QtClassClient/LayerUI/cgraphicmsgcreator.h \
    ../QtClassClient/LayerUI/colorcombox.h \
    ../QtClassClient/LayerUI/IpAddressWidget.h \
    ../QtClassClient/LayerUI/linewidthcombox.h \
    ../QtClassClient/LayerUI/mainwindow.h \
    ../QtClassClient/LayerUI/myscene.h \
    ../QtClassClient/LayerUI/myview.h \
    ../QtClassClient/Message/CModuleAgent.h \
    ../QtClassClient/Message/CMsgObject.h \
    ../QtClassClient/Message/CMsgReceiver.h \
    ../QtClassClient/Message/CMsgSender.h \
    ../QtClassClient/Net/CClientNet.h \
    ../QtClassClient/Reliable/Connections/CAbsConnection.h \
    ../QtClassClient/Reliable/Connections/CAbsSocket.h \
    ../QtClassClient/Reliable/Connections/CConnection.h \
    ../QtClassClient/Reliable/Connections/CHubConnection.h \
    ../QtClassClient/Reliable/Connections/CPeerConnection.h \
    ../QtClassClient/Reliable/Connections/CReliableConnection.h \
    ../QtClassClient/Reliable/Connections/CSynSocket.h \
    ../QtClassClient/Reliable/DataStructure/Pool.h \
    ../QtClassClient/Reliable/DataStructure/TSQueue.h \
    ../QtClassClient/GeneratedFiles/ui_loginwidget.h \
    ../QtClassClient/GeneratedFiles/ui_mainwindow.h \
    ../QtClassClient/GeneratedFiles/ui_settingwidget.h \
    ../QtClassClient/Reliable/DataUnit/CBlock.h \
    ../QtClassClient/Reliable/DataUnit/CBlockManager.h \
    ../QtClassClient/Reliable/DataUnit/CMessage.h \
    ../QtClassClient/Reliable/DataUnit/CPackage.h \
    ../QtClassClient/Reliable/DataUnit/CPeerPacket.h \
    ../QtClassClient/Reliable/DataUnit/UserBase.h \
    ../QtClassClient/Reliable/OSInedependent/libiop/iop_config.h \
    ../QtClassClient/Reliable/OSInedependent/libiop/iop_thread.h \
    ../QtClassClient/Reliable/OSInedependent/libiop/iop_util.h \
    ../QtClassClient/Reliable/OSInedependent/pthread/config.h \
    ../QtClassClient/Reliable/OSInedependent/pthread/context.h \
    ../QtClassClient/Reliable/OSInedependent/pthread/implement.h \
    ../QtClassClient/Reliable/OSInedependent/pthread/pthread.h \
    ../QtClassClient/Reliable/OSInedependent/pthread/sched.h \
    ../QtClassClient/Reliable/OSInedependent/pthread/semaphore.h \
    ../QtClassClient/Reliable/OSInedependent/others.h \
    ../QtClassClient/Reliable/Server/CAbsServer.h \
    ../QtClassClient/Reliable/Server/CAgentServer.h \
    ../QtClassClient/Reliable/Server/CServer.h \
    ../QtClassClient/Reliable/Server/CWSServer.h \
    ../QtClassClient/Reliable/Strategy/CAbsStrategy.h \
    ../QtClassClient/Reliable/Strategy/CDestroyStrategy.h \
    ../QtClassClient/Reliable/Strategy/CWriteFileStrategy.h \
    ../QtClassClient/Reliable/Zip/crypt.h \
    ../QtClassClient/Reliable/Zip/ioapi.h \
    ../QtClassClient/Reliable/Zip/iowin32.h \
    ../QtClassClient/Reliable/Zip/myzip.h \
    ../QtClassClient/Reliable/Zip/unzip.h \
    ../QtClassClient/Reliable/Zip/zconf.h \
    ../QtClassClient/Reliable/Zip/zip.h \
    ../QtClassClient/Reliable/Zip/zlib.h \
    ../QtClassClient/cshape.h \
    ../QtClassClient/stdafx.h \
    ../build-QtClassClient-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Release/ui_loginwidget.h \
    ../build-QtClassClient-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Release/ui_mainwindow.h \
    ../build-QtClassClient-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Release/ui_settingwidget.h \
    UnitTest/tst_cblock.h \
    UnitTest/tst_cblockmanager.h \
    UnitTest/tst_CPackage.h \
    UnitTest/tst_reliable.h \
    common.h \
    UnitTest/tst_cagentserver.h

INCLUDEPATH += ../QtClassClient/Reliable/OSInedependent/pthread
INCLUDEPATH += ../QtClassClient/Reliable/OSInedependent/libiop
INCLUDEPATH += ../build-QtClassClient-Desktop_Qt_5_3_MSVC2010_OpenGL_32bit-Release
INCLUDEPATH += ../QtClassClient/UserInterface
