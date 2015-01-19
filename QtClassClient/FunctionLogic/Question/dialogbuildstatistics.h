#ifndef DIALOGBUILDSTATISTICS_H
#define DIALOGBUILDSTATISTICS_H

#include <QDialog>
#include <QListWidgetItem>

#include "../../BizLogic/datasingleton.h"
#include "cquestionlogicmodule.h"

namespace Ui {
class DialogBuildStatistics;
}

class DialogBuildStatistics : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBuildStatistics(QWidget *parent = 0);
    ~DialogBuildStatistics();

    void setScoreTable(ScoreTable st);

private slots:
    void on_tbDialogExit_clicked();

    void on_rbSortQuestion_clicked();

    void on_rbSortStudent_clicked();


private:
    // change sort view by student/question
    void changeView();

    // show item detail
    void showDetail(const QModelIndex &index);

private:
    Ui::DialogBuildStatistics   *ui;
    DataSingleton               *ds;
    bool                        isSortByStudent;
    ScoreTable                  scoreTable;
    QList<QListWidgetItem*>     listSortStudent;
    QList<QListWidgetItem*>     listSortQuestion;
    map<TS_UINT64, USER_INFO>   stuUsers;
};

#endif // DIALOGBUILDSTATISTICS_H
