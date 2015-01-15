#include "dialogbuildstatistics.h"
#include "ui_dialogbuildstatistics.h"
#include "widgetansweraccountitem.h"
#include "dialogstatisticdetail.h"

#include "cpromptframe.h"   // for _TEST_PROMPT_POS_ macro

// all item was set data about it's userid or question id
const int itemDataID = Qt::UserRole + 1;

// make sure only one statisticdetail dialog is available
// sometimes the dialog will be deleted anywhere else
// so everytime dealloc buildstatistics or statisticdetail, it will be null
static QDialog* preDialog = NULL;

DialogBuildStatistics::DialogBuildStatistics(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DialogBuildStatistics)
    , ds(DataSingleton::getInstance())
    , isSortByStudent(true) {

    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
#ifdef _TEST_PROMPT_POS_
    setGeometry(0, 0, geometry().width(), geometry().height());
#endif

    changeView();
    connect(ui->lwScores, &KineticListWidget::clicked,
            this, &DialogBuildStatistics::showDetail);

    auto fullUser = ds->getAllUsers();
    for (auto iter = fullUser.begin(); iter != fullUser.end(); ++iter) {
        if (ds->getRole(iter->first) == RoleStudent)
            stuUsers.insert(make_pair(iter->first, iter->second));
    }
}

DialogBuildStatistics::~DialogBuildStatistics()
{
    preDialog = NULL;
    delete ui;
}


void DialogBuildStatistics::setScoreTable(ScoreTable st) {
    int totalQuestions = st.correctAnswers.size();
    scoreTable = st;
    ui->lbDialogTitle->setText(QString::fromLocal8Bit("共") + QString::number(st.correctAnswers.size()) +
                               QString::fromLocal8Bit("题"));

    for (auto iter = stuUsers.begin(); iter != stuUsers.end(); ++iter) {
        TS_UINT64 uid = iter->first;
        if (ds->getRole(uid) != RoleStudent)        // work only on student
            continue;

        QListWidgetItem* item = new QListWidgetItem(
                    QString::fromLocal8Bit(reinterpret_cast<char*> (iter->second.username)));
        item->setData(itemDataID, uid);

        ui->lwScores->addItem(item);
        WidgetAnswerAccountItem * itemWidget = new WidgetAnswerAccountItem;
        auto findscore = scoreTable.studentAnswers.find(uid);
        if (findscore != scoreTable.studentAnswers.end()) {
            AnswerList scoreData = findscore->second;
            if (scoreData.size() == 0)
                continue;
            vector<WORD> result = scoreTable.numRightWrong(uid);
            itemWidget->setValue(result[ScoreCorrect], result[ScoreUncorrect], totalQuestions);
        } else {
            itemWidget->setValue(0, 0, totalQuestions);
        }
        ui->lwScores->setItemWidget(item, itemWidget);
        listSortStudent.append(item);
    }

    AnswerList corrects = scoreTable.correctAnswers;
    for (auto iter = corrects.begin(); iter != corrects.end(); ++iter) {
        WORD qid = iter->first;

        QListWidgetItem* item = new QListWidgetItem(
                    QString::fromLocal8Bit("题目") + QString::number(qid));
        ui->lwScores->addItem(item);
        item->setData(itemDataID, qid);
        WidgetAnswerAccountItem * itemWidget = new WidgetAnswerAccountItem;

        vector<WORD> result;
        result.push_back(0);
        result.push_back(0);

        for (auto stus = stuUsers.begin(); stus != stuUsers.end(); ++stus) {
            TS_UINT64 uid = stus->first;
            if (ds->getRole(uid) != RoleStudent)
                continue;
            map<TS_UINT64, AnswerList> sa = scoreTable.studentAnswers;
            auto findscore = sa.find(uid);
            if (findscore != sa.end()) {
                AnswerList al = sa[uid];
                if (al.find(qid) != al.end()) {
                    if (al[qid] == iter->second)
                        result[ScoreCorrect]++;
                    else
                        result[ScoreUncorrect]++;
                }
            }
        }
        itemWidget->setValue(result[ScoreCorrect], result[ScoreUncorrect], stuUsers.size());
        ui->lwScores->setItemWidget(item, itemWidget);
        listSortQuestion.append(item);
    }
    changeView();
}

void DialogBuildStatistics::on_tbDialogExit_clicked()
{
    done(0);
}

void DialogBuildStatistics::changeView() {
    if (isSortByStudent) {
        foreach (QListWidgetItem* item, listSortQuestion) {
            item->setHidden(true);
        }
        foreach (QListWidgetItem* item, listSortStudent) {
            item->setHidden(false);
        }
    } else {
        foreach (QListWidgetItem* item, listSortQuestion) {
            item->setHidden(false);
        }
        foreach (QListWidgetItem* item, listSortStudent) {
            item->setHidden(true);
        }
    }
}

WORD checkState(ScoreTable st, TS_UINT64 uid, WORD qid) {
    auto stuAns = st.studentAnswers;
    auto crtAns = st.correctAnswers;
    if (!stuAns.count(uid)) {
        return ScoreBlank;
    } else {
        if (!stuAns[uid].count(qid)) {
            return ScoreBlank;
        } else if (stuAns[uid][qid] == crtAns[qid]) {
            return ScoreCorrect;
        } else {
            return ScoreUncorrect;
        }
    }
}

#include <QDebug>
void DialogBuildStatistics::showDetail(const QModelIndex &index) {
    QListWidgetItem* item = ui->lwScores->item(index.row());
    TS_UINT64 id = item->data(itemDataID).toULongLong();

    if (preDialog)
        delete preDialog;


    QVector<QString> keys;
    QVector<WORD> value;
    DialogStatisticDetail *d = new DialogStatisticDetail(this);
    if (listSortQuestion.contains(item)) {
        // watch by question, id is question id
        d->setTitle(item->text() +
                    QString::fromLocal8Bit("答题详情"));
        for (auto iter = stuUsers.begin(); iter != stuUsers.end(); ++iter) {
            TS_UINT64 uid = iter->first;
            keys.append(QString::fromLocal8Bit(reinterpret_cast<char*> (iter->second.username)));
            value.append(checkState(scoreTable, uid, id));
        }
    } else if (listSortStudent.contains(item)) {
        // watch by student, id is uid
        d->setTitle(item->text() +
                    QString::fromLocal8Bit("同学答题详情"));

        AnswerList crtAns = scoreTable.correctAnswers;
        for (auto iter = crtAns.begin(); iter != crtAns.end(); ++iter) {
            WORD qid = iter->first;
            keys.append(QString::fromLocal8Bit("题目") + QString::number(qid));
            value.append(checkState(scoreTable, id, qid));
        }
    } else {
        return;
    }
    d->setKeys(keys);
    d->setValues(value);
    d->setGeometry(0, 0, d->width(), d->height());
    preDialog = d;
    d->exec();
    preDialog = NULL;
}

void DialogBuildStatistics::on_rbSortQuestion_clicked()
{
    if (isSortByStudent == false) {
        return;
    }
    if (preDialog) {
        delete preDialog;
        preDialog = NULL;
    }
    isSortByStudent = false;
    changeView();
}

void DialogBuildStatistics::on_rbSortStudent_clicked()
{
    if (isSortByStudent == true) {
        return;
    }
    if (preDialog) {
        delete preDialog;
        preDialog = NULL;
    }
    isSortByStudent = true;
    changeView();
}
