#ifndef CSETTINGSBUTTON_H
#define CSETTINGSBUTTON_H

#include <QToolButton>
#include "ui_settingwidget.h"

class CSettingsButton : public QToolButton
{
    Q_OBJECT
public:
    explicit CSettingsButton(QWidget *parent = 0);

    bool eventFilter(QObject *o, QEvent *e);

private:
    void menuCreate();

    Ui::settingWidget *ui;

signals:

public slots:
};

#endif // CSETTINGSBUTTON_H
