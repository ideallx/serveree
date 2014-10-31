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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Prompt
{
public:
    QLabel *label;
    QToolButton *toolButton;

    void setupUi(QWidget *Prompt)
    {
        if (Prompt->objectName().isEmpty())
            Prompt->setObjectName(QStringLiteral("Prompt"));
        Prompt->resize(335, 203);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Prompt->sizePolicy().hasHeightForWidth());
        Prompt->setSizePolicy(sizePolicy);
        Prompt->setStyleSheet(QStringLiteral(""));
        label = new QLabel(Prompt);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 40, 101, 41));
        toolButton = new QToolButton(Prompt);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(110, 110, 111, 41));
        toolButton->setStyleSheet(QStringLiteral("background-color: red"));

        retranslateUi(Prompt);

        QMetaObject::connectSlotsByName(Prompt);
    } // setupUi

    void retranslateUi(QWidget *Prompt)
    {
        Prompt->setWindowTitle(QApplication::translate("Prompt", "Form", 0));
        label->setText(QApplication::translate("Prompt", "\346\210\221\345\217\221\347\233\233\345\244\247\345\257\214\347\277\201", 0));
        toolButton->setText(QApplication::translate("Prompt", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class Prompt: public Ui_Prompt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROMPT_H
