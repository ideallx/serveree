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

    // return true, trans end;
    bool generateFileData(TS_FILE_PACKET& fmsg);

    void buildCommonInfo(TS_FILE_PACKET& fmsg);

private:
    FILE_CONTENT m_fc;
};

#endif // CFILEMSGGENERATER_H
