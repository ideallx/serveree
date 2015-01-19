#ifndef DIALOGSTATISTICDETAIL_H
#define DIALOGSTATISTICDETAIL_H

#include "../../Reliable/DataUnit/CMessage.h"
#include <QDialog>

namespace Ui {
class DialogStatisticDetail;
}

class DialogStatisticDetail : public QDialog
{
    Q_OBJECT

public:
    explicit DialogStatisticDetail(QWidget *parent = 0);
    ~DialogStatisticDetail();

    void setTitle(const QString title);

    void setKeys(QVector<QString> keys);

    void setValues(QVector<WORD> values);

private slots:
    void on_tbDialogExit_clicked();

private:
    Ui::DialogStatisticDetail *ui;
};

#endif // DIALOGSTATISTICDETAIL_H
