#ifndef CFILEMSGGENERATER_H
#define CFILEMSGGENERATER_H

#include <QString>
#include "../Reliable/DataUnit/CMessage.h"

const int MaxFileName = 30;
typedef struct {
    DWORD nameLen;
    DWORD fileLen;
    DWORD progress;
    unsigned char filename[MaxFileName];
    unsigned char* filecontent;
} FILE_CONTENT;

class CFileMsgGenerater
{
public:
    CFileMsgGenerater();

    bool create(QString filename);

    // return true, trans end;
    bool generateFileData(TS_FILE_PACKET& fmsg);

    void buildCommonInfo(TS_FILE_PACKET& fmsg);

private:
    FILE_CONTENT m_fc;
};

#endif // CFILEMSGGENERATER_H
