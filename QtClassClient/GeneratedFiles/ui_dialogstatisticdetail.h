/********************************************************************************
** Form generated from reading UI file 'dialogstatisticdetail.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGSTATISTICDETAIL_H
#define UI_DIALOGSTATISTICDETAIL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_DialogStatisticDetail
{
public:
    QTableWidget *tableWidget;
    QToolButton *tbDialogExit;
    QLabel *lbDialogTitle;

    void setupUi(QDialog *DialogStatisticDetail)
    {
        if (DialogStatisticDetail->objectName().isEmpty())
            DialogStatisticDetail->setObjectName(QStringLiteral("DialogStatisticDetail"));
        DialogStatisticDetail->resize(663, 435);
        DialogStatisticDetail->setStyleSheet(QStringLiteral(""));
        tableWidget = new QTableWidget(DialogStatisticDetail);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        tableWidget->setGeometry(QRect(40, 80, 581, 321));
        tbDialogExit = new QToolButton(DialogStatisticDetail);
        tbDialogExit->setObjectName(QStringLiteral("tbDialogExit"));
        tbDialogExit->setGeometry(QRect(40, 40, 71, 31));
        tbDialogExit->setAutoRaise(true);
        lbDialogTitle = new QLabel(DialogStatisticDetail);
        lbDialogTitle->setObjectName(QStringLiteral("lbDialogTitle"));
        lbDialogTitle->setGeometry(QRect(140, 20, 511, 41));

        retranslateUi(DialogStatisticDetail);

        QMetaObject::connectSlotsByName(DialogStatisticDetail);
    } // setupUi

    void retranslateUi(QDialog *DialogStatisticDetail)
    {
        DialogStatisticDetail->setWindowTitle(QApplication::translate("DialogStatisticDetail", "Dialog", 0));
        tbDialogExit->setText(QApplication::translate("DialogStatisticDetail", "\345\205\263\351\227\255", 0));
        lbDialogTitle->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogStatisticDetail: public Ui_DialogStatisticDetail {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGSTATISTICDETAIL_H
