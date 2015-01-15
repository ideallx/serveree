/********************************************************************************
** Form generated from reading UI file 'dialogchooseshape.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGCHOOSESHAPE_H
#define UI_DIALOGCHOOSESHAPE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DialogChooseShape
{
public:
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QToolButton *toolButton_2;
    QToolButton *toolButton;
    QToolButton *toolButton_3;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;
    QToolButton *toolButton_7;
    QToolButton *toolButton_8;

    void setupUi(QDialog *DialogChooseShape)
    {
        if (DialogChooseShape->objectName().isEmpty())
            DialogChooseShape->setObjectName(QStringLiteral("DialogChooseShape"));
        DialogChooseShape->resize(446, 327);
        verticalLayout = new QVBoxLayout(DialogChooseShape);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        toolButton_2 = new QToolButton(DialogChooseShape);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/ui/icon/shapeLine.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_2->setIcon(icon);
        toolButton_2->setIconSize(QSize(32, 32));
        toolButton_2->setAutoRaise(true);

        gridLayout->addWidget(toolButton_2, 0, 1, 1, 1);

        toolButton = new QToolButton(DialogChooseShape);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/ui/icon/shapeScript.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon1);
        toolButton->setIconSize(QSize(32, 32));
        toolButton->setAutoRaise(true);

        gridLayout->addWidget(toolButton, 0, 0, 1, 1);

        toolButton_3 = new QToolButton(DialogChooseShape);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/ui/icon/shapeRectangle.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_3->setIcon(icon2);
        toolButton_3->setIconSize(QSize(32, 32));
        toolButton_3->setAutoRaise(true);

        gridLayout->addWidget(toolButton_3, 0, 2, 1, 1);

        toolButton_4 = new QToolButton(DialogChooseShape);
        toolButton_4->setObjectName(QStringLiteral("toolButton_4"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/ui/icon/shapeRoundRectangle.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_4->setIcon(icon3);
        toolButton_4->setIconSize(QSize(32, 32));
        toolButton_4->setAutoRaise(true);

        gridLayout->addWidget(toolButton_4, 0, 3, 1, 1);

        toolButton_5 = new QToolButton(DialogChooseShape);
        toolButton_5->setObjectName(QStringLiteral("toolButton_5"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/ui/icon/shapeHexagon.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_5->setIcon(icon4);
        toolButton_5->setIconSize(QSize(32, 32));
        toolButton_5->setAutoRaise(true);

        gridLayout->addWidget(toolButton_5, 1, 0, 1, 1);

        toolButton_6 = new QToolButton(DialogChooseShape);
        toolButton_6->setObjectName(QStringLiteral("toolButton_6"));

        gridLayout->addWidget(toolButton_6, 1, 1, 1, 1);

        toolButton_7 = new QToolButton(DialogChooseShape);
        toolButton_7->setObjectName(QStringLiteral("toolButton_7"));

        gridLayout->addWidget(toolButton_7, 1, 2, 1, 1);

        toolButton_8 = new QToolButton(DialogChooseShape);
        toolButton_8->setObjectName(QStringLiteral("toolButton_8"));

        gridLayout->addWidget(toolButton_8, 1, 3, 1, 1);


        verticalLayout->addLayout(gridLayout);


        retranslateUi(DialogChooseShape);

        QMetaObject::connectSlotsByName(DialogChooseShape);
    } // setupUi

    void retranslateUi(QDialog *DialogChooseShape)
    {
        DialogChooseShape->setWindowTitle(QApplication::translate("DialogChooseShape", "Dialog", 0));
        toolButton_2->setText(QApplication::translate("DialogChooseShape", "...", 0));
        toolButton->setText(QApplication::translate("DialogChooseShape", "...", 0));
        toolButton_3->setText(QApplication::translate("DialogChooseShape", "...", 0));
        toolButton_4->setText(QApplication::translate("DialogChooseShape", "...", 0));
        toolButton_5->setText(QApplication::translate("DialogChooseShape", "...", 0));
        toolButton_6->setText(QApplication::translate("DialogChooseShape", "...", 0));
        toolButton_7->setText(QApplication::translate("DialogChooseShape", "...", 0));
        toolButton_8->setText(QApplication::translate("DialogChooseShape", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogChooseShape: public Ui_DialogChooseShape {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGCHOOSESHAPE_H
