#include <QAction>
#include <QVBoxLayout>
#include <QMenu>
#include <QPainter>
#include <QColorDialog>
#include <QDebug>

#include "linewidthcombox.h"

static const qreal iconWidth = 200;
static const qreal iconHeight = 30;

LineWidthCombox::LineWidthCombox(QWidget *parent) :
    QToolButton(parent) {
    setPopupMode(QToolButton::InstantPopup);
    setMenu(createLineMenu());
}

LineWidthCombox::~LineWidthCombox() {

}

QMenu* LineWidthCombox::createLineMenu() {
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(0);

    for (int iRow = 0; iRow < 9; iRow++) {
        QAction *action = new QAction(this);
        action->setData(iRow);
        connect(action, &QAction::triggered,
                this, &LineWidthCombox::onWidthChanged);

        QToolButton *tb = new QToolButton;
        tb->setAutoRaise(true);
        tb->setDefaultAction(action);
        tb->setIcon(createLineIcon(iRow));
        tb->setIconSize(QSize(iconWidth, iconHeight));

        layout->addWidget(tb);
        layout->setMargin(0);
    }

    QWidget* widget = new QWidget;
    widget->setLayout(layout);
    widget->setStyleSheet("background-color: rgb(83, 83, 83);");

    QVBoxLayout *vlayout = new QVBoxLayout;
    vlayout->addWidget(widget);
    vlayout->setMargin(0);

    QMenu* lineMenu = new QMenu(this);
    lineMenu->setLayout(vlayout);

    return lineMenu;
}

QIcon LineWidthCombox::createLineIcon(int width) {
    QPixmap pixmap(iconWidth, iconHeight);
    pixmap.fill(QColor(83, 83, 83));
    QPainter painter(&pixmap);
    painter.setPen(QPen(QBrush(Qt::white), width));
    painter.drawLine(10, 10, iconWidth-10, 10);
    return QIcon(pixmap);
}

void LineWidthCombox::onWidthChanged() {
    QAction* theSender = qobject_cast<QAction *>(sender());
    int width = qvariant_cast<int> (theSender->data());
    menu()->close();
    emit signalWidthChanged(width);
}
