/********************************************************************************
** Form generated from reading UI file 'dialogbuildstatistics.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGBUILDSTATISTICS_H
#define UI_DIALOGBUILDSTATISTICS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "kineticlistwidget.h"

QT_BEGIN_NAMESPACE

class Ui_DialogBuildStatistics
{
public:
    KineticListWidget *lwScores;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *lbCorrect;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QLabel *lbWrong;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_3;
    QLabel *lbBlank;
    QLabel *lbNumber;
    QToolButton *tbDialogExit;
    QGroupBox *groupBox;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QRadioButton *rbSortStudent;
    QRadioButton *rbSortQuestion;

    void setupUi(QDialog *DialogBuildStatistics)
    {
        if (DialogBuildStatistics->objectName().isEmpty())
            DialogBuildStatistics->setObjectName(QStringLiteral("DialogBuildStatistics"));
        DialogBuildStatistics->resize(753, 534);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogBuildStatistics->sizePolicy().hasHeightForWidth());
        DialogBuildStatistics->setSizePolicy(sizePolicy);
        DialogBuildStatistics->setStyleSheet(QString::fromUtf8("QLabel#lbTotal, #lbQuestions, #lbNumber {\n"
"	font: 26pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QLabel#lbCorrect, #lbWrong, #lbBlank {\n"
"	font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QDialog {\n"
"	border: 6px solid rgb(166, 174, 101);\n"
"	background-color:white;\n"
"}\n"
"\n"
"QListWidget {\n"
"	border: none;\n"
"}\n"
"\n"
"QListWidget:item {\n"
"	height: 35;\n"
"}\n"
"\n"
"QScrollBar::vertical {\n"
"	width: 3px;\n"
"	background: rgb(166, 166, 166);\n"
"}\n"
"\n"
"QScrollBar:handle:vertical {\n"
"\n"
"}\n"
"\n"
"QToolButton#tbDialogExit {\n"
"	width: 70;\n"
"	height: 40;\n"
"	color: rgb(0, 157, 65);\n"
"	font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	background-color: white;\n"
"}\n"
"\n"
"QGroupBox {\n"
"	border: none;\n"
"}"));
        lwScores = new KineticListWidget(DialogBuildStatistics);
        lwScores->setObjectName(QStringLiteral("lwScores"));
        lwScores->setGeometry(QRect(30, 90, 691, 381));
        layoutWidget = new QWidget(DialogBuildStatistics);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(500, 40, 197, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/icon/ui/icon/blockcorrect.png")));

        horizontalLayout_2->addWidget(label);

        lbCorrect = new QLabel(layoutWidget);
        lbCorrect->setObjectName(QStringLiteral("lbCorrect"));

        horizontalLayout_2->addWidget(lbCorrect);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/icon/ui/icon/blockwrong.png")));

        horizontalLayout_2->addWidget(label_2);

        lbWrong = new QLabel(layoutWidget);
        lbWrong->setObjectName(QStringLiteral("lbWrong"));

        horizontalLayout_2->addWidget(lbWrong);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/icon/ui/icon/blockblank.png")));

        horizontalLayout_2->addWidget(label_3);

        lbBlank = new QLabel(layoutWidget);
        lbBlank->setObjectName(QStringLiteral("lbBlank"));

        horizontalLayout_2->addWidget(lbBlank);

        lbNumber = new QLabel(DialogBuildStatistics);
        lbNumber->setObjectName(QStringLiteral("lbNumber"));
        lbNumber->setGeometry(QRect(310, 20, 151, 46));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lbNumber->sizePolicy().hasHeightForWidth());
        lbNumber->setSizePolicy(sizePolicy1);
        tbDialogExit = new QToolButton(DialogBuildStatistics);
        tbDialogExit->setObjectName(QStringLiteral("tbDialogExit"));
        tbDialogExit->setGeometry(QRect(40, 30, 70, 40));
        tbDialogExit->setAutoRaise(true);
        groupBox = new QGroupBox(DialogBuildStatistics);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(510, 480, 211, 41));
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 20, 186, 18));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        rbSortStudent = new QRadioButton(widget);
        rbSortStudent->setObjectName(QStringLiteral("rbSortStudent"));
        rbSortStudent->setChecked(true);

        horizontalLayout->addWidget(rbSortStudent);

        rbSortQuestion = new QRadioButton(widget);
        rbSortQuestion->setObjectName(QStringLiteral("rbSortQuestion"));

        horizontalLayout->addWidget(rbSortQuestion);


        retranslateUi(DialogBuildStatistics);

        QMetaObject::connectSlotsByName(DialogBuildStatistics);
    } // setupUi

    void retranslateUi(QDialog *DialogBuildStatistics)
    {
        DialogBuildStatistics->setWindowTitle(QApplication::translate("DialogBuildStatistics", "Dialog", 0));
        label->setText(QString());
        lbCorrect->setText(QApplication::translate("DialogBuildStatistics", "\346\255\243\347\241\256", 0));
        label_2->setText(QString());
        lbWrong->setText(QApplication::translate("DialogBuildStatistics", "\351\224\231\350\257\257", 0));
        label_3->setText(QString());
        lbBlank->setText(QApplication::translate("DialogBuildStatistics", "\346\234\252\347\255\224", 0));
        lbNumber->setText(QApplication::translate("DialogBuildStatistics", "\345\205\2610\351\242\230", 0));
        tbDialogExit->setText(QApplication::translate("DialogBuildStatistics", "\345\205\263\351\227\255", 0));
        groupBox->setTitle(QString());
        rbSortStudent->setText(QApplication::translate("DialogBuildStatistics", "\346\214\211\345\255\246\347\224\237\346\216\222\345\210\227", 0));
        rbSortQuestion->setText(QApplication::translate("DialogBuildStatistics", "\346\214\211\351\242\230\347\233\256\346\216\222\345\210\227", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogBuildStatistics: public Ui_DialogBuildStatistics {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGBUILDSTATISTICS_H
