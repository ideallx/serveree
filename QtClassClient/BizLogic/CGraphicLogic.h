#ifndef CGRAPHICLOGIC_H
#define CGRAPHICLOGIC_H

#include "../Reliable/DataUnit/CMessage.h"
#include <map>
#include <QPointF>
#include <QMap>
#include "CBaseLogic.h"

using namespace std;

class CGraphicLogic : public CBaseLogic
{
public:
    CGraphicLogic(CMsgObject* parent = NULL);
    virtual ~CGraphicLogic() {}

    void procIsRemote(const ts_msg& msg);

    void procRecvIsRemote(map<TS_UINT64, ts_msg> sendMap);
};

#endif // CGRAPHICLOGIC_H
