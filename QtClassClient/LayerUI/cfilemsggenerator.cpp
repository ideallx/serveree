#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QDir>
#include "cfilemsggenerator.h"


CFileMsgGenerator::CFileMsgGenerator() {
    memset(&m_fc, 0, sizeof(FILE_CONTENT));
}

bool CFileMsgGenerator::create(QString filename) {
    QFile f(filename);
    f.open(QIODevice::ReadOnly);
    if (!f.isReadable()) {
        qDebug() << "not readable" << filename;
        return false;
    }
    int filelen = f.bytesAvailable();

    m_fc.nameLen = f.fileName().length() + 2;
    m_fc.fileLen = filelen + MaxFileName;
    m_fc.progress = 0;
    m_fc.filecontent = new unsigned char[m_fc.fileLen];
    m_fc.totalPackets = (m_fc.fileLen + MaxTrans - 1) / MaxTrans;   // modules + 1

    memcpy(m_fc.filecontent, f.read(filelen).constData(), filelen);
    memcpy(m_fc.filename, f.fileName().toLatin1().data(), MaxFileName);
    f.close();
}

void CFileMsgGenerator::buildCommonInfo(TS_FILE_PACKET& fmsg) {
    fmsg.head.UID = globalUID;
    fmsg.head.type = COURSEWARE;
    fmsg.isEnd = 0;
    fmsg.totalPackets = m_fc.totalPackets;
}

bool CFileMsgGenerator::generateFileData(TS_FILE_PACKET& fmsg) {
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
    DWORD transThis = 0;

    if (remaining > MaxTrans) {
        transThis = MaxTrans - offset;
    } else {
        transThis = remaining;
    }

    memcpy(fmsg.content + offset,
           m_fc.filecontent + m_fc.progress - MaxFileName,
           transThis);

    m_fc.progress += transThis;

    fmsg.head.size = sizeof(TS_FILE_PACKET) + transThis - MaxTrans + offset;

    if (m_fc.progress >= m_fc.fileLen) {
        fmsg.isEnd = 1;
        delete m_fc.filecontent;
        m_fc.filecontent = 0;
        return true;
    } else {
        return false;
    }
}
