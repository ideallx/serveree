/********************************************************************************
** Form generated from reading UI file 'prompt.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROMPT_H
#define UI_PROMPT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Prompt
{
public:
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *lbPrompt;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pbConfirm;
    QPushButton *pbCancel;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_5;
    QProgressBar *progressBar;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *Prompt)
    {
        if (Prompt->objectName().isEmpty())
            Prompt->setObjectName(QStringLiteral("Prompt"));
        Prompt->resize(323, 175);
        Prompt->setStyleSheet(QLatin1String("QDialog {\n"
"	background-color:white;\n"
"	border: 10px solid rgb(247, 237, 219);\n"
"}\n"
"\n"
"QPushButton {\n"
"    background-color: rgb(255, 101, 48);\n"
"    border-style: outset;\n"
"    font: bold 14px;\n"
"    padding: 6px;\n"
"	color: white\n"
"}\n"
"\n"
"QLabel {\n"
"	color: black;\n"
"}\n"
"\n"
"QPushButton#pbCancel {\n"
"	background-color: rgb(135, 126, 112);\n"
"}"));
        verticalLayout = new QVBoxLayout(Prompt);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(118, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        lbPrompt = new QLabel(Prompt);
        lbPrompt->setObjectName(QStringLiteral("lbPrompt"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\256\213\344\275\223"));
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        lbPrompt->setFont(font);

        horizontalLayout->addWidget(lbPrompt);

        horizontalSpacer_2 = new QSpacerItem(117, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        pbConfirm = new QPushButton(Prompt);
        pbConfirm->setObjectName(QStringLiteral("pbConfirm"));
        pbConfirm->setMinimumSize(QSize(100, 0));
        pbConfirm->setStyleSheet(QStringLiteral(""));

        horizontalLayout_2->addWidget(pbConfirm);

        pbCancel = new QPushButton(Prompt);
        pbCancel->setObjectName(QStringLiteral("pbCancel"));
        pbCancel->setMinimumSize(QSize(100, 0));

        horizontalLayout_2->addWidget(pbCancel);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_5);

        progressBar = new QProgressBar(Prompt);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setMinimumSize(QSize(200, 0));
        progressBar->setMaximumSize(QSize(400, 16777215));
        progressBar->setValue(24);
        progressBar->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(progressBar);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_6);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer_3 = new QSpacerItem(20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);


        retranslateUi(Prompt);

        QMetaObject::connectSlotsByName(Prompt);
    } // setupUi

    void retranslateUi(QDialog *Prompt)
    {
        Prompt->setWindowTitle(QApplication::translate("Prompt", "Dialog", 0));
        lbPrompt->setText(QApplication::translate("Prompt", "TextLabel", 0));
        pbConfirm->setText(QApplication::translate("Prompt", "\347\241\256  \345\256\232", 0));
        pbCancel->setText(QApplication::translate("Prompt", "\345\217\226\346\266\210", 0));
    } // retranslateUi

};

namespace Ui {
    class Prompt: public Ui_Prompt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROMPT_H
