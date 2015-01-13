/********************************************************************************
** Form generated from reading UI file 'dialogbuildquestion.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGBUILDQUESTION_H
#define UI_DIALOGBUILDQUESTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogBuildQuestion
{
public:
    QPushButton *pbAccount;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QToolButton *tbChoiceA;
    QToolButton *tbChoiceB;
    QToolButton *tbChoiceC;
    QToolButton *tbChoiceD;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *tbBoolTrue;
    QToolButton *tbBoolFalse;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_2;
    QToolButton *tbDialogExit;

    void setupUi(QDialog *DialogBuildQuestion)
    {
        if (DialogBuildQuestion->objectName().isEmpty())
            DialogBuildQuestion->setObjectName(QStringLiteral("DialogBuildQuestion"));
        DialogBuildQuestion->resize(882, 420);
        DialogBuildQuestion->setStyleSheet(QString::fromUtf8("QToolButton:!pressed {\n"
"	background-color: rgb(153, 153, 153);\n"
"	height: 113;\n"
"	width: 113;\n"
"	color: white;\n"
"	font: 74pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QToolButton:pressed {\n"
"	background-color: rgb(0, 157, 66);\n"
"}\n"
"\n"
"QPushButton {\n"
"	color:white;\n"
"	background-color: rgb(216, 39, 28);\n"
"	height: 44;\n"
"	width: 140;\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QDialog {\n"
"	border: 6px solid rgb(166, 174, 101);\n"
"	background-color:white;\n"
"}\n"
"\n"
"QLabel {\n"
"	font: 30pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QToolButton#tbDialogExit {\n"
"	color: rgb(0, 157, 65);\n"
"	font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	background-color: white;\n"
"}"));
        pbAccount = new QPushButton(DialogBuildQuestion);
        pbAccount->setObjectName(QStringLiteral("pbAccount"));
        pbAccount->setGeometry(QRect(720, 310, 121, 41));
        layoutWidget = new QWidget(DialogBuildQuestion);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(210, 30, 631, 161));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        tbChoiceA = new QToolButton(layoutWidget);
        tbChoiceA->setObjectName(QStringLiteral("tbChoiceA"));
        tbChoiceA->setCheckable(true);
        tbChoiceA->setAutoRaise(true);

        horizontalLayout->addWidget(tbChoiceA);

        tbChoiceB = new QToolButton(layoutWidget);
        tbChoiceB->setObjectName(QStringLiteral("tbChoiceB"));
        tbChoiceB->setCheckable(true);
        tbChoiceB->setAutoRaise(true);

        horizontalLayout->addWidget(tbChoiceB);

        tbChoiceC = new QToolButton(layoutWidget);
        tbChoiceC->setObjectName(QStringLiteral("tbChoiceC"));
        tbChoiceC->setCheckable(true);
        tbChoiceC->setAutoRaise(true);

        horizontalLayout->addWidget(tbChoiceC);

        tbChoiceD = new QToolButton(layoutWidget);
        tbChoiceD->setObjectName(QStringLiteral("tbChoiceD"));
        tbChoiceD->setCheckable(true);
        tbChoiceD->setAutoRaise(true);

        horizontalLayout->addWidget(tbChoiceD);

        layoutWidget1 = new QWidget(DialogBuildQuestion);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(210, 210, 331, 151));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        tbBoolTrue = new QToolButton(layoutWidget1);
        tbBoolTrue->setObjectName(QStringLiteral("tbBoolTrue"));
        tbBoolTrue->setCheckable(true);
        tbBoolTrue->setAutoRaise(true);

        horizontalLayout_2->addWidget(tbBoolTrue);

        tbBoolFalse = new QToolButton(layoutWidget1);
        tbBoolFalse->setObjectName(QStringLiteral("tbBoolFalse"));
        tbBoolFalse->setCheckable(true);
        tbBoolFalse->setAutoRaise(true);

        horizontalLayout_2->addWidget(tbBoolFalse);

        layoutWidget2 = new QWidget(DialogBuildQuestion);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(30, 60, 161, 271));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget2);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label);

        label_2 = new QLabel(layoutWidget2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_2);

        tbDialogExit = new QToolButton(DialogBuildQuestion);
        tbDialogExit->setObjectName(QStringLiteral("tbDialogExit"));
        tbDialogExit->setGeometry(QRect(40, 10, 70, 40));
        tbDialogExit->setAutoRaise(true);

        retranslateUi(DialogBuildQuestion);

        QMetaObject::connectSlotsByName(DialogBuildQuestion);
    } // setupUi

    void retranslateUi(QDialog *DialogBuildQuestion)
    {
        DialogBuildQuestion->setWindowTitle(QApplication::translate("DialogBuildQuestion", "Dialog", 0));
        pbAccount->setText(QApplication::translate("DialogBuildQuestion", "\346\210\220\347\273\251\347\273\237\350\256\241", 0));
        tbChoiceA->setText(QApplication::translate("DialogBuildQuestion", "A", 0));
        tbChoiceB->setText(QApplication::translate("DialogBuildQuestion", "B", 0));
        tbChoiceC->setText(QApplication::translate("DialogBuildQuestion", "C", 0));
        tbChoiceD->setText(QApplication::translate("DialogBuildQuestion", "D", 0));
        tbBoolTrue->setText(QApplication::translate("DialogBuildQuestion", "T", 0));
        tbBoolFalse->setText(QApplication::translate("DialogBuildQuestion", "F", 0));
        label->setText(QApplication::translate("DialogBuildQuestion", "\351\200\211\346\213\251\351\242\230", 0));
        label_2->setText(QApplication::translate("DialogBuildQuestion", "\346\230\257\351\235\236\351\242\230", 0));
        tbDialogExit->setText(QApplication::translate("DialogBuildQuestion", "\345\205\263\351\227\255", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogBuildQuestion: public Ui_DialogBuildQuestion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGBUILDQUESTION_H
