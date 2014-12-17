#include <QMenu>
#include <QVBoxLayout>
#include <QBitmap>
#include "csettingsbutton.h"

CSettingsButton::CSettingsButton(QWidget *parent) :
    QToolButton(parent)
{
    setPopupMode(QToolButton::InstantPopup);
    menuCreate();

    connect(ui->exitButton, &QToolButton::clicked,
            qApp, &QApplication::quit);     // TODO signal slot in mainwindow
}


void CSettingsButton::menuCreate() {
    QMenu* menu = new QMenu(this);

    QWidget *w = new QWidget(this);
    ui = new Ui::settingWidget;
    ui->setupUi(w);

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(w);
    menu->setLayout(vlayout);

    QPixmap pixmap(":/back/ui/back/combox2.png");
    menu->setMask(pixmap.mask());
    menu->setStyleSheet("background-color: rgb(85, 92, 120);");
    setMenu(menu);
    menu->installEventFilter(this);
}

bool CSettingsButton::eventFilter(QObject *o, QEvent *e) {
    if(e->type() == QEvent::Show) {
        QMenu *event_menu = static_cast<QMenu *>(o);
        if(event_menu == NULL)
            return false;
        const QPoint point = parentWidget()->mapToGlobal(geometry().bottomRight());
        event_menu->move(point.x() - event_menu->width() + 1, point.y() + 2);
    }
    return QToolButton::eventFilter(o, e);
}
