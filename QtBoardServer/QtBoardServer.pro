#-------------------------------------------------
#
# Project created by QtCreator 2014-09-24T14:45:58
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = QtBoardServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    Connections/CAbsConnection.cpp \
    Connections/CAbsSocket.cpp \
    Connections/CConnection.cpp \
    Connections/CHubConnection.cpp \
    Connections/CPeerConnection.cpp \
    Connections/CReliableConnection.cpp \
    Connections/CSynSocket.cpp \
    DataUnit/CBlock.cpp \
    DataUnit/CBlockManager.cpp \
    DataUnit/CMessage.cpp \
    DataUnit/CPackage.cpp \
    OSInedependent/others.cpp \
    OSInedependent/libiop/iop_thread.c \
    OSInedependent/libiop/iop_util.c \
    OSInedependent/pthread/cleanup.c \
    OSInedependent/pthread/global.c \
    OSInedependent/pthread/pthread_cancel.c \
    OSInedependent/pthread/pthread_create.c \
    OSInedependent/pthread/pthread_detach.c \
    OSInedependent/pthread/pthread_equal.c \
    OSInedependent/pthread/pthread_getspecific.c \
    OSInedependent/pthread/pthread_key_create.c \
    OSInedependent/pthread/pthread_key_delete.c \
    OSInedependent/pthread/pthread_kill.c \
    OSInedependent/pthread/pthread_mutex_consistent.c \
    OSInedependent/pthread/pthread_mutex_destroy.c \
    OSInedependent/pthread/pthread_mutex_init.c \
    OSInedependent/pthread/pthread_mutex_lock.c \
    OSInedependent/pthread/pthread_mutex_trylock.c \
    OSInedependent/pthread/pthread_mutex_unlock.c \
    OSInedependent/pthread/pthread_mutexattr_destroy.c \
    OSInedependent/pthread/pthread_self.c \
    OSInedependent/pthread/pthread_setschedparam.c \
    OSInedependent/pthread/pthread_setspecific.c \
    OSInedependent/pthread/pthread_testcancel.c \
    OSInedependent/pthread/pthread_win32_attach_detach_np.c \
    OSInedependent/pthread/ptw32_callUserDestroyRoutines.c \
    OSInedependent/pthread/ptw32_MCS_lock.c \
    OSInedependent/pthread/ptw32_mutex_check_need_init.c \
    OSInedependent/pthread/ptw32_new.c \
    OSInedependent/pthread/ptw32_processInitialize.c \
    OSInedependent/pthread/ptw32_processTerminate.c \
    OSInedependent/pthread/ptw32_reuse.c \
    OSInedependent/pthread/ptw32_threadDestroy.c \
    OSInedependent/pthread/ptw32_threadStart.c \
    OSInedependent/pthread/ptw32_throw.c \
    OSInedependent/pthread/ptw32_tkAssocCreate.c \
    OSInedependent/pthread/ptw32_tkAssocDestroy.c \
    OSInedependent/pthread/sched_get_priority_max.c \
    OSInedependent/pthread/sched_get_priority_min.c \
    OSInedependent/pthread/sched_yield.c \
    OSInedependent/pthread/sem_destroy.c \
    OSInedependent/pthread/sem_init.c \
    OSInedependent/pthread/sem_post.c \
    OSInedependent/pthread/sem_wait.c \
    OSInedependent/pthread/w32_CancelableWait.c \
    Server/CAbsServer.cpp \
    Server/CAgentServer.cpp \
    Server/CServer.cpp \
    Server/CWSServer.cpp \
    Strategy/CAbsStrategy.cpp \
    Strategy/CDestroyStrategy.cpp \
    Strategy/CWriteFileStrategy.cpp \
    Zip/myzip.cpp \
    Zip/ioapi.c \
    Zip/iowin32.c \
    Zip/unzip.c \
    Zip/zip.c

HEADERS += \
    Connections/CAbsConnection.h \
    Connections/CAbsSocket.h \
    Connections/CConnection.h \
    Connections/CHubConnection.h \
    Connections/CPeerConnection.h \
    Connections/CReliableConnection.h \
    Connections/CSynSocket.h \
    DataStructure/Pool.h \
    DataStructure/TSQueue.h \
    DataUnit/CBlock.h \
    DataUnit/CBlockManager.h \
    DataUnit/CMessage.h \
    DataUnit/CPackage.h \
    DataUnit/CPeerPacket.h \
    DataUnit/UserBase.h \
    OSInedependent/others.h \
    OSInedependent/libiop/iop_config.h \
    OSInedependent/libiop/iop_thread.h \
    OSInedependent/libiop/iop_util.h \
    OSInedependent/pthread/config.h \
    OSInedependent/pthread/context.h \
    OSInedependent/pthread/implement.h \
    OSInedependent/pthread/pthread.h \
    OSInedependent/pthread/sched.h \
    OSInedependent/pthread/semaphore.h \
    Server/CAbsServer.h \
    Server/CAgentServer.h \
    Server/CServer.h \
    Server/CWSServer.h \
    Strategy/CAbsStrategy.h \
    Strategy/CDestroyStrategy.h \
    Strategy/CWriteFileStrategy.h \
    Zip/crypt.h \
    Zip/ioapi.h \
    Zip/iowin32.h \
    Zip/myzip.h \
    Zip/unzip.h \
    Zip/zconf.h \
    Zip/zip.h \
    Zip/zlib.h \
    Stdafx.h

OTHER_FILES += \
    Zip/zdll.lib \
    Zip/zlib.lib \
    Zip/zlib1.dll

INCLUDEPATH += include
INCLUDEPATH += OSInedependent
INCLUDEPATH += OSInedependent/pthread
INCLUDEPATH += OSInedependent/libiop

LIBS += C:\Users\Fulaan\Documents\GitHub\server\EBoardServer\EBoardServer\Zip\zlib.lib
LIBS += C:\Users\Fulaan\Documents\GitHub\server\EBoardServer\EBoardServer\Zip\zdll.lib

