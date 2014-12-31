#include "CQuestionLogic.h"

CQuestionLogic::CQuestionLogic(CMsgObject* parent):
    CBaseLogic(parent) {
}

CQuestionGenerator::CQuestionGenerator() {

}

void CQuestionGenerator::buildCommonInfo(TS_QUESTION_PACKET& qmsg) {
    qmsg.head.size = sizeof(TS_QUESTION_PACKET);
    qmsg.head.type = QUESTION;
}

void CQuestionGenerator::generateQuestionData(TS_QUESTION_PACKET &qmsg, WORD type, WORD time) {
    buildCommonInfo(qmsg);
    qmsg.qType = type;
    qmsg.time = time;
}
