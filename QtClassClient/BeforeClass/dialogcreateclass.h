#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "../Message/CMsgObject.h"
#include "../BizLogic/datasingleton.h"

namespace Ui {
class Dialog;
}

class DialogCreateClass : public QDialog, public CMsgObject
{
    Q_OBJECT

public:
    explicit DialogCreateClass(QWidget *parent = NULL,
                               CMsgObject* msgParent = NULL);
    ~DialogCreateClass();

private slots:
    void on_buttonBox_accepted();

signals:
    void createClass(QString classname);

private:
    Ui::Dialog *ui;
    DataSingleton* ds;
};

#endif // DIALOG_H
