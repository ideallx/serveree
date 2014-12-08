#ifndef CRACEGENERATOR_H
#define CRACEGENERATOR_H

#include "../../Reliable/DataUnit/CMessage.h"

class CRaceGenerator
{
public:
    CRaceGenerator();

    void buildCommonInfo(TS_RACE_PACKET& rmsg);

    void generateRaceData(TS_RACE_PACKET &rmsg, WORD type,
                          WORD writeTime, TS_UINT64 stuUID);
};

#endif // CRACEGENERATOR_H