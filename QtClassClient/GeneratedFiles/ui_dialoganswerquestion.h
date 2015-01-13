/********************************************************************************
** Form generated from reading UI file 'dialoganswerquestion.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGANSWERQUESTION_H
#define UI_DIALOGANSWERQUESTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_DialogAnswerQuestion
{
public:
    QHBoxLayout *horizontalLayout;
    QToolButton *tbChoiceA;
    QToolButton *tbChoiceB;
    QToolButton *tbChoiceC;
    QToolButton *tbChoiceD;

    void setupUi(QDialog *DialogAnswerQuestion)
    {
        if (DialogAnswerQuestion->objectName().isEmpty())
            DialogAnswerQuestion->setObjectName(QStringLiteral("DialogAnswerQuestion"));
        DialogAnswerQuestion->resize(684, 180);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(DialogAnswerQuestion->sizePolicy().hasHeightForWidth());
        DialogAnswerQuestion->setSizePolicy(sizePolicy);
        DialogAnswerQuestion->setStyleSheet(QString::fromUtf8("QToolButton {\n"
"	background-color: rgb(0, 157, 66);\n"
"	height: 113;\n"
"	width: 113;\n"
"	color: white;\n"
"	font: 74pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QDialog {\n"
"	border: 6px solid rgb(166, 174, 101);\n"
"	background-color:white;\n"
"}"));
        horizontalLayout = new QHBoxLayout(DialogAnswerQuestion);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tbChoiceA = new QToolButton(DialogAnswerQuestion);
        tbChoiceA->setObjectName(QStringLiteral("tbChoiceA"));
        tbChoiceA->setAutoRaise(true);

        horizontalLayout->addWidget(tbChoiceA);

        tbChoiceB = new QToolButton(DialogAnswerQuestion);
        tbChoiceB->setObjectName(QStringLiteral("tbChoiceB"));
        tbChoiceB->setAutoRaise(true);

        horizontalLayout->addWidget(tbChoiceB);

        tbChoiceC = new QToolButton(DialogAnswerQuestion);
        tbChoiceC->setObjectName(QStringLiteral("tbChoiceC"));
        tbChoiceC->setAutoRaise(true);

        horizontalLayout->addWidget(tbChoiceC);

        tbChoiceD = new QToolButton(DialogAnswerQuestion);
        tbChoiceD->setObjectName(QStringLiteral("tbChoiceD"));
        tbChoiceD->setAutoRaise(true);

        horizontalLayout->addWidget(tbChoiceD);


        retranslateUi(DialogAnswerQuestion);

        QMetaObject::connectSlotsByName(DialogAnswerQuestion);
    } // setupUi

    void retranslateUi(QDialog *DialogAnswerQuestion)
    {
        DialogAnswerQuestion->setWindowTitle(QApplication::translate("DialogAnswerQuestion", "Dialog", 0));
        tbChoiceA->setText(QApplication::translate("DialogAnswerQuestion", "A", 0));
        tbChoiceB->setText(QApplication::translate("DialogAnswerQuestion", "B", 0));
        tbChoiceC->setText(QApplication::translate("DialogAnswerQuestion", "C", 0));
        tbChoiceD->setText(QApplication::translate("DialogAnswerQuestion", "D", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogAnswerQuestion: public Ui_DialogAnswerQuestion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGANSWERQUESTION_H
