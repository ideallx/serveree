/********************************************************************************
** Form generated from reading UI file 'dialogchoosereplay.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCHOOSEREPLAY_H
#define UI_DIALOGCHOOSEREPLAY_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogChooseReplay
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QToolButton *tbBack;
    QSpacerItem *horizontalSpacer;
    QToolButton *tbExit;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout;
    QToolButton *toolButton13;
    QToolButton *toolButton15;
    QToolButton *toolButton16;
    QToolButton *toolButton;
    QToolButton *toolButton3;
    QToolButton *toolButton2;
    QToolButton *toolButton6;
    QToolButton *toolButton7;
    QToolButton *toolButton5;
    QToolButton *toolButton8;
    QToolButton *toolButton11;
    QToolButton *toolButton9;
    QToolButton *toolButton12;
    QToolButton *toolButton10;
    QToolButton *toolButton4;
    QToolButton *toolButton14;
    QToolButton *toolButton17;
    QToolButton *toolButton18;
    QToolButton *toolButton19;
    QToolButton *toolButton20;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *DialogChooseReplay)
    {
        if (DialogChooseReplay->objectName().isEmpty())
            DialogChooseReplay->setObjectName(QStringLiteral("DialogChooseReplay"));
        DialogChooseReplay->resize(600, 400);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogChooseReplay->sizePolicy().hasHeightForWidth());
        DialogChooseReplay->setSizePolicy(sizePolicy);
        DialogChooseReplay->setStyleSheet(QString::fromUtf8("QDialog {\n"
"	background-image: url(:/back/ui/back/background.jpg);\n"
"}\n"
"\n"
"QToolButton {\n"
"	color: green;\n"
"	background-color: rgb(221, 232, 197)\n"
"}\n"
"\n"
"QToolButton:hover {\n"
"	color: white;\n"
"	background-color: rgb(95, 170, 88)\n"
"}\n"
"\n"
"QToolButton#tbBack, #tbExit {\n"
"	color: white;\n"
"	font: 12pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	background-color: transparent\n"
"}\n"
"\n"
"QToolButton#tbBack:hover, #tbExit:hover {\n"
"	background-color: rgb(212, 63, 39);\n"
"}\n"
""));
        verticalLayout = new QVBoxLayout(DialogChooseReplay);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tbBack = new QToolButton(DialogChooseReplay);
        tbBack->setObjectName(QStringLiteral("tbBack"));
        tbBack->setAutoRaise(true);

        horizontalLayout->addWidget(tbBack);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        tbExit = new QToolButton(DialogChooseReplay);
        tbExit->setObjectName(QStringLiteral("tbExit"));
        tbExit->setAutoRaise(true);

        horizontalLayout->addWidget(tbExit);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(0);
        gridLayout->setVerticalSpacing(15);
        toolButton13 = new QToolButton(DialogChooseReplay);
        toolButton13->setObjectName(QStringLiteral("toolButton13"));
        toolButton13->setMinimumSize(QSize(120, 40));
        toolButton13->setMaximumSize(QSize(120, 40));
        toolButton13->setAutoRaise(true);

        gridLayout->addWidget(toolButton13, 3, 0, 1, 1);

        toolButton15 = new QToolButton(DialogChooseReplay);
        toolButton15->setObjectName(QStringLiteral("toolButton15"));
        toolButton15->setMinimumSize(QSize(120, 40));
        toolButton15->setMaximumSize(QSize(120, 40));
        toolButton15->setAutoRaise(true);

        gridLayout->addWidget(toolButton15, 3, 2, 1, 1);

        toolButton16 = new QToolButton(DialogChooseReplay);
        toolButton16->setObjectName(QStringLiteral("toolButton16"));
        toolButton16->setMinimumSize(QSize(120, 40));
        toolButton16->setMaximumSize(QSize(120, 40));
        toolButton16->setAutoRaise(true);

        gridLayout->addWidget(toolButton16, 3, 3, 1, 1);

        toolButton = new QToolButton(DialogChooseReplay);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setMinimumSize(QSize(120, 40));
        toolButton->setMaximumSize(QSize(120, 40));
        toolButton->setAutoRaise(true);

        gridLayout->addWidget(toolButton, 0, 0, 1, 1);

        toolButton3 = new QToolButton(DialogChooseReplay);
        toolButton3->setObjectName(QStringLiteral("toolButton3"));
        toolButton3->setMinimumSize(QSize(120, 40));
        toolButton3->setMaximumSize(QSize(120, 40));
        toolButton3->setAutoRaise(true);

        gridLayout->addWidget(toolButton3, 0, 2, 1, 1);

        toolButton2 = new QToolButton(DialogChooseReplay);
        toolButton2->setObjectName(QStringLiteral("toolButton2"));
        toolButton2->setMinimumSize(QSize(120, 40));
        toolButton2->setMaximumSize(QSize(120, 40));
        toolButton2->setAutoRaise(true);

        gridLayout->addWidget(toolButton2, 0, 1, 1, 1);

        toolButton6 = new QToolButton(DialogChooseReplay);
        toolButton6->setObjectName(QStringLiteral("toolButton6"));
        toolButton6->setMinimumSize(QSize(120, 40));
        toolButton6->setMaximumSize(QSize(120, 40));
        toolButton6->setAutoRaise(true);

        gridLayout->addWidget(toolButton6, 1, 1, 1, 1);

        toolButton7 = new QToolButton(DialogChooseReplay);
        toolButton7->setObjectName(QStringLiteral("toolButton7"));
        toolButton7->setMinimumSize(QSize(120, 40));
        toolButton7->setMaximumSize(QSize(120, 40));
        toolButton7->setAutoRaise(true);

        gridLayout->addWidget(toolButton7, 1, 2, 1, 1);

        toolButton5 = new QToolButton(DialogChooseReplay);
        toolButton5->setObjectName(QStringLiteral("toolButton5"));
        toolButton5->setMinimumSize(QSize(120, 40));
        toolButton5->setMaximumSize(QSize(120, 40));
        toolButton5->setAutoRaise(true);

        gridLayout->addWidget(toolButton5, 1, 0, 1, 1);

        toolButton8 = new QToolButton(DialogChooseReplay);
        toolButton8->setObjectName(QStringLiteral("toolButton8"));
        toolButton8->setMinimumSize(QSize(120, 40));
        toolButton8->setMaximumSize(QSize(120, 40));
        toolButton8->setAutoRaise(true);

        gridLayout->addWidget(toolButton8, 1, 3, 1, 1);

        toolButton11 = new QToolButton(DialogChooseReplay);
        toolButton11->setObjectName(QStringLiteral("toolButton11"));
        toolButton11->setMinimumSize(QSize(120, 40));
        toolButton11->setMaximumSize(QSize(120, 40));
        toolButton11->setAutoRaise(true);

        gridLayout->addWidget(toolButton11, 2, 2, 1, 1);

        toolButton9 = new QToolButton(DialogChooseReplay);
        toolButton9->setObjectName(QStringLiteral("toolButton9"));
        toolButton9->setMinimumSize(QSize(120, 40));
        toolButton9->setMaximumSize(QSize(120, 40));
        toolButton9->setAutoRaise(true);

        gridLayout->addWidget(toolButton9, 2, 0, 1, 1);

        toolButton12 = new QToolButton(DialogChooseReplay);
        toolButton12->setObjectName(QStringLiteral("toolButton12"));
        toolButton12->setMinimumSize(QSize(120, 40));
        toolButton12->setMaximumSize(QSize(120, 40));
        toolButton12->setAutoRaise(true);

        gridLayout->addWidget(toolButton12, 2, 3, 1, 1);

        toolButton10 = new QToolButton(DialogChooseReplay);
        toolButton10->setObjectName(QStringLiteral("toolButton10"));
        toolButton10->setMinimumSize(QSize(120, 40));
        toolButton10->setMaximumSize(QSize(120, 40));
        toolButton10->setAutoRaise(true);

        gridLayout->addWidget(toolButton10, 2, 1, 1, 1);

        toolButton4 = new QToolButton(DialogChooseReplay);
        toolButton4->setObjectName(QStringLiteral("toolButton4"));
        toolButton4->setMinimumSize(QSize(120, 40));
        toolButton4->setMaximumSize(QSize(120, 40));
        toolButton4->setAutoRaise(true);

        gridLayout->addWidget(toolButton4, 0, 3, 1, 1);

        toolButton14 = new QToolButton(DialogChooseReplay);
        toolButton14->setObjectName(QStringLiteral("toolButton14"));
        toolButton14->setMinimumSize(QSize(120, 40));
        toolButton14->setMaximumSize(QSize(120, 40));
        toolButton14->setAutoRaise(true);

        gridLayout->addWidget(toolButton14, 3, 1, 1, 1);

        toolButton17 = new QToolButton(DialogChooseReplay);
        toolButton17->setObjectName(QStringLiteral("toolButton17"));
        toolButton17->setMinimumSize(QSize(120, 40));
        toolButton17->setMaximumSize(QSize(120, 40));
        toolButton17->setAutoRaise(true);

        gridLayout->addWidget(toolButton17, 4, 0, 1, 1);

        toolButton18 = new QToolButton(DialogChooseReplay);
        toolButton18->setObjectName(QStringLiteral("toolButton18"));
        toolButton18->setMinimumSize(QSize(120, 40));
        toolButton18->setMaximumSize(QSize(120, 40));
        toolButton18->setAutoRaise(true);

        gridLayout->addWidget(toolButton18, 4, 1, 1, 1);

        toolButton19 = new QToolButton(DialogChooseReplay);
        toolButton19->setObjectName(QStringLiteral("toolButton19"));
        toolButton19->setMinimumSize(QSize(120, 40));
        toolButton19->setMaximumSize(QSize(120, 40));
        toolButton19->setAutoRaise(true);

        gridLayout->addWidget(toolButton19, 4, 2, 1, 1);

        toolButton20 = new QToolButton(DialogChooseReplay);
        toolButton20->setObjectName(QStringLiteral("toolButton20"));
        toolButton20->setMinimumSize(QSize(120, 40));
        toolButton20->setMaximumSize(QSize(120, 40));
        toolButton20->setAutoRaise(true);

        gridLayout->addWidget(toolButton20, 4, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        retranslateUi(DialogChooseReplay);

        QMetaObject::connectSlotsByName(DialogChooseReplay);
    } // setupUi

    void retranslateUi(QDialog *DialogChooseReplay)
    {
        DialogChooseReplay->setWindowTitle(QApplication::translate("DialogChooseReplay", "Dialog", 0));
        tbBack->setText(QApplication::translate("DialogChooseReplay", "<-", 0));
        tbExit->setText(QApplication::translate("DialogChooseReplay", "X", 0));
        toolButton13->setText(QString());
        toolButton15->setText(QString());
        toolButton16->setText(QString());
        toolButton->setText(QApplication::translate("DialogChooseReplay", "\344\270\276\344\270\252\346\240\227\345\255\220", 0));
        toolButton3->setText(QString());
        toolButton2->setText(QString());
        toolButton6->setText(QString());
        toolButton7->setText(QString());
        toolButton5->setText(QString());
        toolButton8->setText(QString());
        toolButton11->setText(QString());
        toolButton9->setText(QString());
        toolButton12->setText(QString());
        toolButton10->setText(QString());
        toolButton4->setText(QString());
        toolButton14->setText(QString());
        toolButton17->setText(QString());
        toolButton18->setText(QString());
        toolButton19->setText(QString());
        toolButton20->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class DialogChooseReplay: public Ui_DialogChooseReplay {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCHOOSEREPLAY_H
