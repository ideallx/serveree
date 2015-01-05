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
        correctAnswers.insert(make_pair(qmsg.questionID, qmsg.answer));
        if (ds->getSelfRole() == RoleStudent)
            emit questionSented(qmsg.qFormat);
        qDebug() << "add correct" << qmsg.questionID << qmsg.answer;
        break;
    case QuestionAnswer:
        addData(qmsg.head.UID, qmsg.questionID, qmsg.qFormat, qmsg.answer);
        break;
    case QuestionStatistics:
        emit questionStatictics(scores);
        break;
    default:
        break;
    }
}

void CQuestionModule::addData(TS_UINT64 uid, WORD questionID, WORD format, WORD answer) {
    qDebug() << "check correct" << questionID << answer;
    if (correctAnswers.find(questionID) == correctAnswers.end()) {  // not find the answer
        return;
    }

    qDebug() << "recv uid:" << uid
             << "question id: " << questionID
             << "question format:" << format
             << "question answer:" << answer;
    auto iter = scores.find(uid);
    if (iter == scores.end()) {
        vector<WORD> table;
        table.push_back(0);
        table.push_back(0);
        scores.insert(make_pair(uid, table));
    }

    if (correctAnswers[questionID] == answer) {
        scores[uid][ScoreCorrect]++;
    } else {
        scores[uid][ScoreUncorrect]++;
    }
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
