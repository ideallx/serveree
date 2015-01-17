/********************************************************************************
** Form generated from reading UI file 'settingwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGWIDGET_H
#define UI_SETTINGWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_settingWidget
{
public:
    QVBoxLayout *verticalLayout;
    QToolButton *tbChangeStyle;
    QToolButton *exitButton;

    void setupUi(QWidget *settingWidget)
    {
        if (settingWidget->objectName().isEmpty())
            settingWidget->setObjectName(QStringLiteral("settingWidget"));
        settingWidget->resize(115, 84);
        verticalLayout = new QVBoxLayout(settingWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tbChangeStyle = new QToolButton(settingWidget);
        tbChangeStyle->setObjectName(QStringLiteral("tbChangeStyle"));
        tbChangeStyle->setMinimumSize(QSize(115, 42));
        tbChangeStyle->setMaximumSize(QSize(115, 42));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(11);
        tbChangeStyle->setFont(font);
        tbChangeStyle->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        tbChangeStyle->setAutoRaise(true);

        verticalLayout->addWidget(tbChangeStyle);

        exitButton = new QToolButton(settingWidget);
        exitButton->setObjectName(QStringLiteral("exitButton"));
        exitButton->setMinimumSize(QSize(115, 42));
        exitButton->setMaximumSize(QSize(115, 42));
        exitButton->setFont(font);
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/ui/icon/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        exitButton->setIcon(icon);
        exitButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        exitButton->setAutoRaise(true);

        verticalLayout->addWidget(exitButton);


        retranslateUi(settingWidget);

        QMetaObject::connectSlotsByName(settingWidget);
    } // setupUi

    void retranslateUi(QWidget *settingWidget)
    {
        settingWidget->setWindowTitle(QApplication::translate("settingWidget", "Form", 0));
        tbChangeStyle->setText(QApplication::translate("settingWidget", "\350\203\214\346\231\257\345\210\207\346\215\242", 0));
        exitButton->setText(QApplication::translate("settingWidget", "\351\200\200\345\207\272\350\275\257\344\273\266", 0));
    } // retranslateUi

};

namespace Ui {
    class settingWidget: public Ui_settingWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGWIDGET_H
