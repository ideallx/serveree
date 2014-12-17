/********************************************************************************
** Form generated from reading UI file 'dialogclasschoose.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCLASSCHOOSE_H
#define UI_DIALOGCLASSCHOOSE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogClassChoose
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *tbCreateClass;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *tbCloseClass;

    void setupUi(QDialog *DialogClassChoose)
    {
        if (DialogClassChoose->objectName().isEmpty())
            DialogClassChoose->setObjectName(QStringLiteral("DialogClassChoose"));
        DialogClassChoose->resize(492, 313);
        verticalLayoutWidget = new QWidget(DialogClassChoose);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(120, 70, 241, 161));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tbCreateClass = new QToolButton(verticalLayoutWidget);
        tbCreateClass->setObjectName(QStringLiteral("tbCreateClass"));

        horizontalLayout->addWidget(tbCreateClass);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));

        verticalLayout->addLayout(horizontalLayout_2);

        tbCloseClass = new QToolButton(DialogClassChoose);
        tbCloseClass->setObjectName(QStringLiteral("tbCloseClass"));
        tbCloseClass->setGeometry(QRect(320, 30, 67, 18));

        retranslateUi(DialogClassChoose);

        QMetaObject::connectSlotsByName(DialogClassChoose);
    } // setupUi

    void retranslateUi(QDialog *DialogClassChoose)
    {
        DialogClassChoose->setWindowTitle(QApplication::translate("DialogClassChoose", "Dialog", 0));
        tbCreateClass->setText(QApplication::translate("DialogClassChoose", "\345\210\233\345\273\272\350\257\276\345\240\202", 0));
        tbCloseClass->setText(QApplication::translate("DialogClassChoose", "\345\205\263\351\227\255\350\257\276\345\240\202", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogClassChoose: public Ui_DialogClassChoose {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCLASSCHOOSE_H
