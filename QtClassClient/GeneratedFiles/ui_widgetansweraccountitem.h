/********************************************************************************
** Form generated from reading UI file 'widgetansweraccountitem.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGETANSWERACCOUNTITEM_H
#define UI_WIDGETANSWERACCOUNTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WidgetAnswerAccountItem
{
public:
    QHBoxLayout *horizontalLayout;
    QLabel *lbCorrect;
    QLabel *lbWrong;
    QLabel *lbBlank;

    void setupUi(QWidget *WidgetAnswerAccountItem)
    {
        if (WidgetAnswerAccountItem->objectName().isEmpty())
            WidgetAnswerAccountItem->setObjectName(QStringLiteral("WidgetAnswerAccountItem"));
        WidgetAnswerAccountItem->resize(660, 33);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WidgetAnswerAccountItem->sizePolicy().hasHeightForWidth());
        WidgetAnswerAccountItem->setSizePolicy(sizePolicy);
        WidgetAnswerAccountItem->setStyleSheet(QString::fromUtf8("QLabel#lbCorrect {\n"
"	background-color: rgb(33, 160, 73);\n"
"}\n"
"\n"
"QLabel#lbWrong {\n"
"	background-color: rgb(200, 0, 0);\n"
"}\n"
"\n"
"QLabel#lbBlank {\n"
"	background-color: rgb(119, 119, 117);\n"
"}\n"
"\n"
"QLabel {\n"
"	font: 14pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: white;\n"
"}\n"
"\n"
"Line {\n"
"	background-color: black;\n"
"}"));
        horizontalLayout = new QHBoxLayout(WidgetAnswerAccountItem);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setSizeConstraint(QLayout::SetFixedSize);
        horizontalLayout->setContentsMargins(110, 4, 4, 4);
        lbCorrect = new QLabel(WidgetAnswerAccountItem);
        lbCorrect->setObjectName(QStringLiteral("lbCorrect"));
        lbCorrect->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lbCorrect);

        lbWrong = new QLabel(WidgetAnswerAccountItem);
        lbWrong->setObjectName(QStringLiteral("lbWrong"));
        lbWrong->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lbWrong);

        lbBlank = new QLabel(WidgetAnswerAccountItem);
        lbBlank->setObjectName(QStringLiteral("lbBlank"));
        lbBlank->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lbBlank);


        retranslateUi(WidgetAnswerAccountItem);

        QMetaObject::connectSlotsByName(WidgetAnswerAccountItem);
    } // setupUi

    void retranslateUi(QWidget *WidgetAnswerAccountItem)
    {
        WidgetAnswerAccountItem->setWindowTitle(QApplication::translate("WidgetAnswerAccountItem", "Form", 0));
        lbCorrect->setText(QString());
        lbWrong->setText(QString());
        lbBlank->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WidgetAnswerAccountItem: public Ui_WidgetAnswerAccountItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGETANSWERACCOUNTITEM_H
