#include <QFile>
#include <QByteArray>
#include "cfilemsggenerater.h"


CFileMsgGenerater::CFileMsgGenerater() {
    memset(&m_fc, 0, sizeof(TS_FILE_PACKET));
}

bool CFileMsgGenerater::create(QString filename) {
    QFile f(filename);
    if (!f.isReadable())
        return false;
    m_fc.filecontent = f.readAll().data();
    m_fc.nameLen = f.fileName().length();
    m_fc.fileLen = f.bytesAvailable() + MaxFileName;
    m_fc.filename = f.fileName();
    m_fc.progress = 0;
}

bool CFileMsgGenerater::generateFileData(TS_FILE_PACKET& fmsg) {
    if (m_fc.nameLen == 0)
        return true;

    DWORD offset = 0;
    buildCommonInfo(fmsg);

    if (m_fc.progress == 0) {
        memcpy(fmsg.content, m_fc.filename, MaxFileName);
        m_fc.progress += MaxFileName;
        offset = MaxFileName;
    }

    DWORD remaining = m_fc.fileLen - m_fc.progress;
    if (m_fc.progress != m_fc.fileLen) {
        if (remaining > MaxTrans) {
            memcpy(fmsg.content + offset,
                   m_fc.filecontent + m_fc.progress - MaxFileName,
                   MaxTrans - offset);
        } else {
            memcpy(fmsg.content + offset,
                   m_fc.filecontent + m_fc.progress - MaxFileName,
                   remaining);
        }
        m_fc.progress += MaxTrans;
    }

    if (m_fc.progress >= m_fc.fileLen) {
        return true;
    } else {
        return false;
    }
}
