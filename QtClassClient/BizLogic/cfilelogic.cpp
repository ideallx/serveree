#include "cfilelogic.h"
#include "../LayerUI/mainwindow.h"

CFileLogic::CFileLogic(CMsgObject* parent):
    CBaseLogic(parent),
    m_waitForNewFile(true),
    m_fileBeginSubseq(0),
    m_fileTotalPackets(0) {
}


void CFileLogic::procRecvIsRemote(map<TS_UINT64, ts_msg> sendMap) {
    for (auto iter = sendMap.begin(); iter != sendMap.end(); iter++) {
        TS_FILE_PACKET* fmsg = (TS_FILE_PACKET*) &(iter->second);
        int offset = 0;
        if (m_waitForNewFile) {
            QString filename = QString::fromLocal8Bit((char *) fmsg->content);
            offset += MaxFileName;
            m_writingFile.setFileName(filename);
            m_writingFile.open(QIODevice::WriteOnly);

            m_waitForNewFile = false;
            m_fileBeginSubseq = fmsg->head.subSeq;
            m_fileTotalPackets = fmsg->totalPackets;
        }

        if (m_writingFile.isWritable()) {
            DWORD writeSize = MaxTrans - (sizeof(TS_FILE_PACKET) - fmsg->head.size);
            m_writingFile.write((const char*) (fmsg->content + offset), writeSize - offset);
//            qDebug() << "progress:" <<
//                        (fmsg->head.subSeq - m_fileBeginSubseq + 1) * 100 / m_fileTotalPackets;

            if (fmsg->isEnd) {
                qDebug() << "succes";
                m_waitForNewFile = true;
                m_writingFile.close();
                // TODO
                memcpy(fmsg->content, m_writingFile.fileName().toLatin1().data(), MaxFileName);
                sendToUp(iter->second, 0, 0, true);
            }
        } else {
            qDebug() << "cant write file";
        }
    }
}
