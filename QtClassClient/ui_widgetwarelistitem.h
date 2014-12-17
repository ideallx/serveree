/********************************************************************************
** Form generated from reading UI file 'widgetwarelistitem.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETWARELISTITEM_H
#define UI_WIDGETWARELISTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetWareListItem
{
public:
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *tbRun;
    QToolButton *tbRemove;

    void setupUi(QWidget *WidgetWareListItem)
    {
        if (WidgetWareListItem->objectName().isEmpty())
            WidgetWareListItem->setObjectName(QStringLiteral("WidgetWareListItem"));
        WidgetWareListItem->resize(303, 30);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WidgetWareListItem->sizePolicy().hasHeightForWidth());
        WidgetWareListItem->setSizePolicy(sizePolicy);
        horizontalLayout = new QHBoxLayout(WidgetWareListItem);
        horizontalLayout->setSpacing(10);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 1, 1, 1);
        horizontalSpacer = new QSpacerItem(179, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        tbRun = new QToolButton(WidgetWareListItem);
        tbRun->setObjectName(QStringLiteral("tbRun"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/ui/icon/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbRun->setIcon(icon);
        tbRun->setIconSize(QSize(25, 25));
        tbRun->setAutoRaise(true);

        horizontalLayout->addWidget(tbRun);

        tbRemove = new QToolButton(WidgetWareListItem);
        tbRemove->setObjectName(QStringLiteral("tbRemove"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/ui/icon/remove.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbRemove->setIcon(icon1);
        tbRemove->setIconSize(QSize(25, 25));
        tbRemove->setAutoRaise(true);

        horizontalLayout->addWidget(tbRemove);


        retranslateUi(WidgetWareListItem);

        QMetaObject::connectSlotsByName(WidgetWareListItem);
    } // setupUi

    void retranslateUi(QWidget *WidgetWareListItem)
    {
        WidgetWareListItem->setWindowTitle(QApplication::translate("WidgetWareListItem", "Form", 0));
        tbRun->setText(QApplication::translate("WidgetWareListItem", "\350\277\220\350\241\214", 0));
        tbRemove->setText(QApplication::translate("WidgetWareListItem", "\345\210\240\351\231\244", 0));
    } // retranslateUi

};

namespace Ui {
    class WidgetWareListItem: public Ui_WidgetWareListItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETWARELISTITEM_H
