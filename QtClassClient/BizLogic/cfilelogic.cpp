#include "cfilelogic.h"
#include "../LayerUI/mainwindow.h"

CFileLogic::CFileLogic(CMsgObject* parent):
    CBaseLogic(parent),
    m_waitForNewFile(true) {
}


void CFileLogic::procRecvIsRemote(map<TS_UINT64, ts_msg> sendMap) {
    for (auto iter = sendMap.begin(); iter != sendMap.end(); iter++) {
        TS_FILE_PACKET* fmsg = (TS_FILE_PACKET*) &(iter->second);
        qDebug() << fmsg->head.subSeq;

        int offset = 0;
        if (m_waitForNewFile) {
            char filename[MaxFileName];
            memcpy(filename, fmsg->content, MaxFileName);
            offset += MaxFileName;
            m_writingFile.setFileName(filename);
            m_writingFile.open(QIODevice::WriteOnly);
            m_waitForNewFile = false;
        }

        DWORD writeSize = MaxTrans + fmsg->head.size - sizeof(TS_FILE_PACKET);
        m_writingFile.write((const char*) (fmsg->content + offset), writeSize);

        if (fmsg->isEnd) {
            m_waitForNewFile = true;
            m_writingFile.close();
            MainWindow* ui = static_cast<MainWindow*>(p_Parent->getAgent()->getModule("UI"));
            // prompt
        }
    }
}
