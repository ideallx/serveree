#ifndef CPLAYERGENERATOR_H
#define CPLAYERGENERATOR_H

#include "../../Reliable/DataUnit/CMessage.h"
#include <QString>
#include <QFile>

class CPlayerGenerator
{
public:
    CPlayerGenerator();

    bool create(QString filename);

    bool generatePlayerData(TS_PLAYER_PACKET& pmsg, WORD action);

    void buildCommonInfo(TS_PLAYER_PACKET& pmsg);

private:
    QString curFileName;
    int pos;
    int subpos;
};

#endif // CPLAYERGENERATOR_H
