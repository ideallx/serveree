#include <QAction>
#include <QVBoxLayout>
#include <QMenu>
#include <QPainter>
#include <QColorDialog>
#include <QDebug>

#include "../Reliable/DataUnit/CMessage.h"
#include "cshapechooser.h"

static const qreal iconWidth = 150;
static const qreal iconHeight = 40;

CShapeChooser::CShapeChooser(QWidget *parent) :
    QToolButton(parent) {
    setPopupMode(QToolButton::InstantPopup);
    setMenu(createLineMenu());
}

CShapeChooser::~CShapeChooser() {

}

QMenu* CShapeChooser::createLineMenu() {
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(0);

    for (int iRow = 1; iRow < 7; iRow++) {
        QAction *action = new QAction(this);
        action->setData(iRow);
        connect(action, &QAction::triggered,
                this, &CShapeChooser::onTypeChanged);

        QToolButton *tb = new QToolButton;
        tb->setIconSize(QSize(iconWidth, iconHeight));
        tb->setAutoRaise(true);
        tb->setDefaultAction(action);
        tb->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        tb->setIcon(createLineIcon(iRow));
        tb->setText(createLineText(iRow));
        tb->setFont(QFont(tb->font().family(), 16));

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
    // lineMenu->setStyleSheet("padding-left:10px;");

    return lineMenu;
}

QIcon CShapeChooser::createLineIcon(int shapeType) {
    QPixmap p;
    switch (shapeType) {
    case SCRIPTS:
        p.load(":/icon/ui/icon/shapeScript.png");
        break;
    case ELLIPSE:
        p.load(":/icon/ui/icon/shapeEllipse.png");
        break;
    case LINE:
        p.load(":/icon/ui/icon/shapeLine.png");
        break;
    case RECTANGLE:
        p.load(":/icon/ui/icon/shapeRectangle.png");
        break;
    case ROUNDRECT:
        p.load(":/icon/ui/icon/shapeRoundRectangle.png");
        break;
    case HEXAGON:
        p.load(":/icon/ui/icon/shapeHexagon.png");
        break;
    default:
        p.fill(Qt::white);
        break;
    }

    return QIcon(p);
}

QString CShapeChooser::createLineText(int shapeType) {
    QString s;
    switch (shapeType) {
    case SCRIPTS:
        s = QStringLiteral("    曲线工具");
        break;
    case ELLIPSE:
        s = QStringLiteral("    椭圆工具");
        break;
    case LINE:
        s = QStringLiteral("    直线工具");
        break;
    case RECTANGLE:
        s = QStringLiteral("    矩形工具");
        break;
    case ROUNDRECT:
        s = QStringLiteral("    圆角矩形工具");
        break;
    case HEXAGON:
        s = QStringLiteral("    六角形工具");
        break;
    default:
        s = QStringLiteral("    未知工具");
        break;
    }

    return s;
}


void CShapeChooser::onTypeChanged() {
    QAction* theSender = qobject_cast<QAction *>(sender());
    int width = qvariant_cast<int> (theSender->data());
    menu()->close();
    emit signalShapeChanged(width);
}
