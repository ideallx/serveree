#include "cracegenerator.h"

CRaceGenerator::CRaceGenerator()
{
}

void CRaceGenerator::buildCommonInfo(TS_RACE_PACKET& rmsg) {
    rmsg.head.size = sizeof(TS_RACE_PACKET);
    rmsg.head.type = RACE;
    rmsg.head.UID = globalUID;
}

void CRaceGenerator::generateRaceData(TS_RACE_PACKET &rmsg, WORD type,
                                      WORD writeTime, TS_UINT64 stuUID) {
	buildCommonInfo(rmsg);
    rmsg.raceType = type;
    switch (type) {
    case RaceInit:
        rmsg.teacherUID = globalUID;
        rmsg.writingTime = writeTime;
        break;
    case RaceRace:
        rmsg.studentUID = globalUID;
        break;
    case RaceResult:
        rmsg.teacherUID = globalUID;
        rmsg.studentUID = stuUID;
        rmsg.writingTime = writeTime;
        break;
    default:
        break;
    }
}
