#ifndef CGRAPHICLOGIC_H
#define CGRAPHICLOGIC_H

#include <QPointF>
#include <QMap>
#include "CBaseLogic.h"

struct lastState {
    DWORD graphicSeq;
    WORD shapeID;
    QPointF point;
};

class CGraphicLogic : public CBaseLogic
{
public:
    CGraphicLogic(CMsgObject* parent = NULL);
    virtual ~CGraphicLogic() {}

    virtual bool procMsg(const ts_msg& msg, bool isRemote);

private:
    QMap<TS_UINT64, struct lastState> last;
};

#endif // CGRAPHICLOGIC_H
