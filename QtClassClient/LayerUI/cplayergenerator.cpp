#include <QDebug>
#include "cplayergenerator.h"

CPlayerGenerator::CPlayerGenerator() :
    pos(0),
    subpos(0) {
}

bool CPlayerGenerator::create(QString filename) {
    QFile f(filename);
    f.open(QIODevice::ReadOnly);
    if (!f.isReadable()) {
        qDebug() << "not readable" << filename;
        return false;
    }
    curFileName = filename;
    return true;
}


bool CPlayerGenerator::generatePlayerData(TS_PLAYER_PACKET& pmsg, WORD action) {
    buildCommonInfo(pmsg);

    switch (action) {
    case ActionNext:
        pos++;
        subpos = 0;
        break;
    case ActionPrev:
        pos++;
        subpos = 0;
        break;
    case ActionSubNext:
        subpos++;
        break;
    case ActionSubPrev:
        if (subpos > 0)
            subpos --;
        break;
    case ActionStart:
        pos = 0;
        subpos = 0;
        break;
    default:
        break;
    }

    pmsg.toPosition = pos;
    pmsg.toSubPosition = subpos;
    pmsg.pa = action;
    pmsg.step = 1;

    return true;
}

void CPlayerGenerator::buildCommonInfo(TS_PLAYER_PACKET& pmsg) {
    pmsg.head.UID = globalUID;
    pmsg.head.type = PLAYERCONTROL;
    memcpy(pmsg.filename, curFileName.toLatin1().data(), MaxFileName);
}
