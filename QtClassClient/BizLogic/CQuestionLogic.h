#ifndef _BIZLOGIC_CQUESTIONLOGIC_H
#define _BIZLOGIC_CQUESTIONLOGIC_H

#include "../Reliable/DataUnit/CMessage.h"
#include "CBaseLogic.h"

#include <map>
#include <vector>

using namespace std;

// uid q1 Ans, q2 Ans, q3 Ans ......
typedef map<WORD, WORD> AnswerList;

class ScoreTable {
public:
    map<TS_UINT64, AnswerList> studentAnswers;
    AnswerList correctAnswers;

    vector<WORD> numRightWrong(TS_UINT64 uid) {
        vector<WORD> result;
        result.push_back(0);
        result.push_back(0);
        if (studentAnswers.find(uid) == studentAnswers.end()) {
            return result;
        }
        AnswerList al = studentAnswers[uid];
        for (auto iter = al.begin(); iter != al.end(); ++iter) {
            WORD qid = iter->first;
            WORD ans = iter->second;
            if (correctAnswers.find(qid) != correctAnswers.end()) {
                if (correctAnswers[qid] == ans) {
                    result[ScoreCorrect]++;
                } else {
                    result[ScoreUncorrect]++;
                }
            }
        }
        return result;
    }
};

static ScoreTable scores;
static WORD questionid;

class CQuestionModule : public QObject {
    Q_OBJECT

public:
    CQuestionModule();
    void process(TS_QUESTION_PACKET &qmsg);

    int totalQuestion();
    ScoreTable getScoreTable();

signals:
    void questionSented(WORD format, WORD answer);

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

private:
    void buildCommonInfo(TS_QUESTION_PACKET& qmsg);
};


#endif // _BIZLOGIC_CQUESTIONLOGIC_H
