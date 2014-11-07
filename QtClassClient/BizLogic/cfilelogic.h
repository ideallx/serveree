#ifndef CFILELOGIC_H
#define CFILELOGIC_H

#include "../Reliable/DataUnit/CMessage.h"
#include "CBaseLogic.h"
#include <map>
#include <QFile>

class CFileLogic : public CBaseLogic
{
public:
    CFileLogic(CMsgObject* parent = NULL);
    virtual ~CFileLogic() {}

    virtual void procRecvIsRemote(map<TS_UINT64, ts_msg> sendMap);

private:
    QFile m_writingFile;
    bool  m_waitForNewFile;
    DWORD m_fileBeginSubseq;
    DWORD m_fileTotalPackets;
};

#endif // CFILELOGIC_H
