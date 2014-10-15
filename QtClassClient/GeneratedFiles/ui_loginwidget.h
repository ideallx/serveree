/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_loginWidget
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QFrame *line_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QToolButton *toolButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *loginWidget)
    {
        if (loginWidget->objectName().isEmpty())
            loginWidget->setObjectName(QStringLiteral("loginWidget"));
        loginWidget->resize(157, 161);
        loginWidget->setStyleSheet(QLatin1String("background-color: rgb(85, 92, 120);\n"
"\n"
"QLineEdit {\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        verticalLayout = new QVBoxLayout(loginWidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(loginWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setPixmap(QPixmap(QString::fromUtf8(":/icon/ui/icon/username.png")));

        horizontalLayout_2->addWidget(label);

        lineEdit = new QLineEdit(loginWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 30));
        lineEdit->setStyleSheet(QStringLiteral(""));
        lineEdit->setMaxLength(20);
        lineEdit->setFrame(false);
        lineEdit->setCursorMoveStyle(Qt::LogicalMoveStyle);

        horizontalLayout_2->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        line = new QFrame(loginWidget);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(loginWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/icon/ui/icon/password.png")));

        horizontalLayout_3->addWidget(label_2);

        lineEdit_2 = new QLineEdit(loginWidget);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setMinimumSize(QSize(0, 30));
        lineEdit_2->setMaxLength(15);
        lineEdit_2->setFrame(false);
        lineEdit_2->setEchoMode(QLineEdit::Password);

        horizontalLayout_3->addWidget(lineEdit_2);


        verticalLayout->addLayout(horizontalLayout_3);

        line_2 = new QFrame(loginWidget);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        verticalSpacer_3 = new QSpacerItem(134, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        toolButton = new QToolButton(loginWidget);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/word/ui/word/enterclass.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton->setIcon(icon);
        toolButton->setIconSize(QSize(85, 26));
        toolButton->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(134, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        QWidget::setTabOrder(lineEdit, lineEdit_2);
        QWidget::setTabOrder(lineEdit_2, toolButton);

        retranslateUi(loginWidget);

        QMetaObject::connectSlotsByName(loginWidget);
    } // setupUi

    void retranslateUi(QWidget *loginWidget)
    {
        loginWidget->setWindowTitle(QApplication::translate("loginWidget", "Form", 0));
        label->setText(QString());
        lineEdit->setPlaceholderText(QApplication::translate("loginWidget", "\347\224\250\346\210\267\345\220\215", 0));
        label_2->setText(QString());
        lineEdit_2->setPlaceholderText(QApplication::translate("loginWidget", "\345\257\206\347\240\201", 0));
        toolButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class loginWidget: public Ui_loginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
