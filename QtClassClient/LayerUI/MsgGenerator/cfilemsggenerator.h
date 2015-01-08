#ifndef CFILEMSGGENERATER_H
#define CFILEMSGGENERATER_H

#include <QString>
#include <QFile>
#include "../../Reliable/DataUnit/CMessage.h"


class CFileMsgGenerator
{
public:
    CFileMsgGenerator();

    bool create(QString filename);

    QString filename();

    // return true, trans end;
    bool generateFileData(TS_FILE_PACKET& fmsg);

    void buildCommonInfo(TS_FILE_PACKET& fmsg);

    int getProgress();

private:
    FILE_CONTENT m_fc;
};

#endif // CFILEMSGGENERATER_H
