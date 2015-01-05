#ifndef _BIZLOGIC_CQUESTIONLOGIC_H
#define _BIZLOGIC_CQUESTIONLOGIC_H

#include "../Reliable/DataUnit/CMessage.h"
#include "CBaseLogic.h"

#include <map>
#include <vector>

using namespace std;
typedef map<TS_UINT64, vector<WORD>> ScoreTable;  // uid, correctNum, errNum


static ScoreTable scores;
static map<int, WORD> correctAnswers;
static WORD questionid;

class CQuestionModule : public QObject {
    Q_OBJECT

public:
    CQuestionModule();
    void process(TS_QUESTION_PACKET &qmsg);

    inline int totalQuestion() { return correctAnswers.size(); }

signals:
    void questionSented(WORD format);
    void questionStatictics(ScoreTable scores);

private:
    void addData(TS_UINT64 uid, WORD questionID, WORD format, WORD answer);
    DataSingleton* ds;

};


class CQuestionGenerator {
public:
    CQuestionGenerator();

    void init();        // init a new question

    void generateQuestionData(TS_QUESTION_PACKET &qmsg, WORD type, WORD format,
                              WORD answer, WORD time = 60);

    inline ScoreTable getScoreTable() { return scores; }
private:
    void buildCommonInfo(TS_QUESTION_PACKET& qmsg);
};


#endif // _BIZLOGIC_CQUESTIONLOGIC_H
