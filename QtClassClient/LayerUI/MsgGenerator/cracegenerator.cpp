#include "cracegenerator.h"
#include "../../BizLogic/datasingleton.h"

CRaceGenerator::CRaceGenerator()
{
    ds = DataSingleton::getInstance();
}

void CRaceGenerator::buildCommonInfo(TS_RACE_PACKET& rmsg) {
    rmsg.head.size = sizeof(TS_RACE_PACKET);
    rmsg.head.type = RACE;
}

void CRaceGenerator::generateRaceData(TS_RACE_PACKET &rmsg, WORD type,
                                      WORD writeTime, TS_UINT64 stuUID) {
	buildCommonInfo(rmsg);
    rmsg.raceType = type;
    switch (type) {
    case RaceInit:
        rmsg.teacherUID = ds->getUID();
        rmsg.writingTime = writeTime;
        break;
    case RaceRace:
        rmsg.studentUID = ds->getUID();
        break;
    case RaceResult:
        rmsg.teacherUID = ds->getUID();
        rmsg.studentUID = stuUID;
        rmsg.writingTime = writeTime;
        break;
    default:
        break;
    }
}
