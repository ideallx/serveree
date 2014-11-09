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
        qDebug() << fmsg->head.subSeq;
        int offset = 0;
        if (m_waitForNewFile) {
            char filename[MaxFileName];
            memcpy(filename, fmsg->content, MaxFileName);
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
                ui->addWareList(m_writingFile.fileName());
                ui->sendResultPrompt(SuccessDownload);
            }
        } else {
            qDebug() << "cant write file";
        }
    }
}