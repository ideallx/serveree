#ifndef _BIZLOGIC_CQUESTIONLOGIC_H
#define _BIZLOGIC_CQUESTIONLOGIC_H

#include "../Reliable/DataUnit/CMessage.h"
#include "CBaseLogic.h"

class CQuestionLogic : public CBaseLogic
{
public:
    CQuestionLogic(CMsgObject* parent = NULL);
};


class CQuestionGenerator {
public:
    CQuestionGenerator();

    void buildCommonInfo(TS_QUESTION_PACKET& qmsg);

    void generateQuestionData(TS_QUESTION_PACKET &qmsg, WORD type, WORD time = 60);
};


#endif // _BIZLOGIC_CQUESTIONLOGIC_H
