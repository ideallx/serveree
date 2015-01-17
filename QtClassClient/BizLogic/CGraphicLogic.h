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
};

#endif // CGRAPHICLOGIC_H
