#include "ColorCombox.h"

#include <QAction>
#include <QGridLayout>
#include <QMenu>
#include <QPainter>
#include <QColorDialog>

static const int iconWidth = 20;

const QColor colors[6][8] =
{
    {QColor(0, 0, 0, 255), QColor(170, 0, 0, 255), QColor(0, 85, 0, 255), QColor(170, 85, 0, 255),
    QColor(0, 170, 0, 255), QColor(170, 170, 0, 255), QColor(0, 255, 0, 255), QColor(170, 250, 0, 255)},

    {QColor(0, 0, 127, 255), QColor(170, 0, 127, 255), QColor(0, 85, 127, 255), QColor(170, 85, 127, 255),
    QColor(0, 170, 127, 255), QColor(170, 170, 127, 255), QColor(0, 255, 127, 255), QColor(170, 255, 127, 255)},

    {QColor(0, 0, 255, 255), QColor(170, 0, 255, 255), QColor(0, 85, 255, 255), QColor(170, 85, 255, 255),
    QColor(0, 170, 255, 255), QColor(170, 170, 255, 255), QColor(0, 255, 255, 255), QColor(170, 255, 255, 255)},

    {QColor(85, 0, 0, 255), QColor(255, 0, 0, 255), QColor(85, 85, 0, 255), QColor(255, 85, 0, 255),
    QColor(85, 170, 0, 255), QColor(255, 170, 0, 255), QColor(85, 255, 0, 255), QColor(255, 255, 0, 255)},

    {QColor(85, 0, 127, 255), QColor(255, 0, 127, 255), QColor(85, 85, 127, 255), QColor(255, 85, 127, 255),
    QColor(85, 170, 127, 255), QColor(255, 170, 127, 255), QColor(85, 255, 127, 255), QColor(255, 255, 127, 255)},

    {QColor(85, 0, 255, 255), QColor(255, 0, 255, 255), QColor(85, 85, 255, 255), QColor(255, 85, 255, 255),
    QColor(85, 170, 255, 255), QColor(255, 170, 255, 255), QColor(85, 255, 255, 255), QColor(255, 255, 255, 255)}
};

ColorCombox::ColorCombox(QWidget *parent)
    : QToolButton(parent)
{
    setPopupMode(QToolButton::InstantPopup);
    setMenu(createColorMenu(SLOT(OnColorChanged()), SLOT(OnShowColorBoard())));
    setAutoFillBackground(true);
}

ColorCombox::~ColorCombox()
{

}

void ColorCombox::setButtonIcon(const QString &imageFile, QColor color)
{
    setIcon(createColorToolButtonIcon(imageFile, color));
}

QMenu *ColorCombox::createColorMenu(const char *slot, const char *slotColorBoard)
{
    Q_UNUSED(slotColorBoard);
    // 设置透明色
//    QAction *pActionTransparent = new QAction(this);
//    pActionTransparent->setData(QColor(0, 0, 0, 0));
//    pActionTransparent->setText(tr("transparent_set"));
//    connect(pActionTransparent, SIGNAL(triggered()), this, slot);
//    QToolButton *pBtnTransparent = new QToolButton;
//    pBtnTransparent->setFixedSize(QSize(142, 16));
//    pBtnTransparent->setText(tr("transparent_set"));
//    pBtnTransparent->setDefaultAction(pActionTransparent);

    // 基本色
    QGridLayout *pGridLayout = new QGridLayout;
    pGridLayout->setAlignment(Qt::AlignCenter);
    pGridLayout->setContentsMargins(0, 0, 0, 0);
    pGridLayout->setSpacing(0);

    for (int iRow = 0; iRow < 6; iRow++)
    {
        for (int iCol = 0; iCol < 8; iCol++)
        {
            QAction *action = new QAction(this);
            action->setData(colors[iRow][iCol]);
            action->setIcon(createColorIcon(colors[iRow][iCol]));
            connect(action, SIGNAL(triggered()), this, slot);

            QToolButton *pBtnColor = new QToolButton;
            pBtnColor->setFixedSize(QSize(iconWidth, iconWidth));
            pBtnColor->setAutoRaise(true);
            pBtnColor->setDefaultAction(action);

            pGridLayout->addWidget(pBtnColor, iRow, iCol);
        }
    }

    QWidget *widget = new QWidget;
    widget->setLayout(pGridLayout);

    QVBoxLayout *pVLayout = new QVBoxLayout;
   // pVLayout->addWidget(pBtnTransparent);
    pVLayout->addWidget(widget);

    QMenu *colorMenu = new QMenu(this);
    colorMenu->setLayout(pVLayout);

    return colorMenu;
}

QIcon ColorCombox::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(iconWidth, iconWidth);
    pixmap.fill(Qt::transparent);

    QPainter painter(&pixmap);
    QPixmap image(imageFile);

    QRect target(0, 0, iconWidth, iconWidth);
    QRect source(0, 0, iconWidth, iconWidth);
    painter.fillRect(QRect(0, iconWidth, iconWidth, 0), color);
    painter.drawPixmap(target, image, source);
    return QIcon(pixmap);

    return QIcon("");
}

QIcon ColorCombox::createColorIcon(QColor color)
{
    QPixmap pixmap(iconWidth, iconWidth);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, iconWidth, iconWidth), color);

    return QIcon(pixmap);
}

void ColorCombox::OnColorChanged()
{
    QAction *pFillColorAction = new QAction(this);
    pFillColorAction = qobject_cast<QAction *>(sender());
    QColor color = qvariant_cast<QColor>(pFillColorAction->data());

    this->menu()->close();

//    this->setStyleSheet(QString("background-color: rgb(%1, %2, %3);").
//                        arg(color.red()).
//                            arg(color.green()).
//                                arg(color.blue()));

    emit sigColorChanged(color);
}

void ColorCombox::OnShowColorBoard()
{
    this->menu()->close();
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (!color.isValid())
        return;

    emit sigColorChanged(color);
}
