#ifndef DIALOGCLASSCHOOSE_H
#define DIALOGCLASSCHOOSE_H

#include <QDialog>
#include "../Message/CMsgObject.h"

namespace Ui {
class DialogClassChoose;
}

class DialogClassChoose : public QDialog, public CMsgObject
{
    Q_OBJECT

public:
    explicit DialogClassChoose(QWidget *parent = 0);
    ~DialogClassChoose();

    void ProcessMessage(ts_msg& msg, WPARAM wParam, LPARAM lParam, BOOL isRemote);

signals:
    void classCreated(QString className);

private slots:
    void on_tbCreateClass_clicked();

    void on_listWidget_doubleClicked(const QModelIndex &index);

public slots:
    void addClassItem(QString className);

private:
    Ui::DialogClassChoose *ui;
};

#endif // DIALOGCLASSCHOOSE_H
