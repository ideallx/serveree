#include "CQuestionLogic.h"
#include <QDebug>

CQuestionModule::CQuestionModule()
    : ds(DataSingleton::getInstance()) {

}

void CQuestionModule::process(TS_QUESTION_PACKET& qmsg) {
    qDebug() << "recv type: " << qmsg.qType;
    questionid = qmsg.questionID;
    switch (qmsg.qType) {
    case QuestionInit:
        scores.correctAnswers.insert(make_pair(qmsg.questionID, qmsg.answer));
        if (ds->getSelfRole() == RoleStudent)
            emit questionSented(qmsg.qFormat, qmsg.answer);
        qDebug() << "add correct" << qmsg.questionID << qmsg.answer;
        break;
    case QuestionAnswer:
        addData(qmsg.head.UID, qmsg.questionID, qmsg.qFormat, qmsg.answer);
        break;
    case QuestionStatistics:
        break;
    default:
        break;
    }
}

int CQuestionModule::totalQuestion() {
    return scores.correctAnswers.size();
}

ScoreTable CQuestionModule::getScoreTable() {
    return scores;
}

void CQuestionModule::addData(TS_UINT64 uid, WORD questionID, WORD format, WORD answer) {
    qDebug() << "check correct" << questionID << answer;
    if (scores.correctAnswers.find(questionID) == scores.correctAnswers.end()) {  // not find the answer
        return;
    }

    qDebug() << "recv uid:" << uid
             << "question id: " << questionID
             << "question format:" << format
             << "question answer:" << answer;
    auto iter = scores.studentAnswers.find(uid);
    if (iter == scores.studentAnswers.end()) {
        AnswerList table;
        scores.studentAnswers.insert(make_pair(uid, table));
    }

    scores.studentAnswers[uid].insert(make_pair(questionID, answer));
//    if (correctAnswers[questionID] == answer) {
//        scores[uid][ScoreCorrect]++;
//    } else {
//        scores[uid][ScoreUncorrect]++;
//    }
}


CQuestionGenerator::CQuestionGenerator() {
    questionid = 0;
}

void CQuestionGenerator::init() {
    ++questionid;
}

void CQuestionGenerator::buildCommonInfo(TS_QUESTION_PACKET& qmsg) {
    qmsg.head.size = sizeof(TS_QUESTION_PACKET);
    qmsg.head.type = QUESTION;
}

void CQuestionGenerator::generateQuestionData(TS_QUESTION_PACKET &qmsg, WORD type, 
                                              WORD format, WORD answer, WORD time) {
    qDebug() << "question type:" << type;
    buildCommonInfo(qmsg);
    qmsg.questionID = questionid;
    qmsg.qType = type;
    qmsg.qFormat = format;
    qmsg.time = time;
    qmsg.answer = answer;
}
