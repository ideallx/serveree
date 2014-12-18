/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QToolButton *tbExit;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_5;
    QLineEdit *leUsername;
    QHBoxLayout *horizontalLayout_6;
    QLineEdit *lePassword;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *toolButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label_2;
    QToolButton *tbEnterClass;
    QProgressBar *pbDownload;
    QLabel *lbPrompt;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *verticalSpacer;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QStringLiteral("LoginDialog"));
        LoginDialog->resize(600, 400);
        LoginDialog->setStyleSheet(QLatin1String("QDialog {\n"
"	background-image: url(:/back/ui/back/background.jpg);\n"
"}\n"
"\n"
"QLabel {\n"
"	color: rgb(0, 255, 127);\n"
"}\n"
"\n"
"QLabel#lbPrompt {\n"
"	color: rgb(0, 0, 0);\n"
"}\n"
"\n"
"#QToolButton#tbExit:hover[autoRaise = \"true\"] {\n"
"	background-image: url(:/icon/ui/icon/close2.png);\n"
"}\n"
"\n"
"QToolButton#tbEnterClass {\n"
"	background-color: rgb(0, 130, 54);\n"
"	color: white;\n"
"	font: 16px;\n"
"}\n"
"\n"
"QToolButton#tbEnterClass:!enabled {\n"
"}\n"
"\n"
"QLineEdit {\n"
"	font: 16px;\n"
"	padding-left: 40px;\n"
"}\n"
"\n"
"QLineEdit#leUsername {\n"
"	background-image: url(:/icon/ui/icon/llusername.png);\n"
"}\n"
"\n"
"QLineEdit#lePassword {\n"
"	background-image: url(:/icon/ui/icon/llpassword.png);\n"
"}"));
        verticalLayout_2 = new QVBoxLayout(LoginDialog);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        tbExit = new QToolButton(LoginDialog);
        tbExit->setObjectName(QStringLiteral("tbExit"));
        tbExit->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/ui/icon/close1.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral(":/icon/ui/icon/close1.png"), QSize(), QIcon::Normal, QIcon::On);
        tbExit->setIcon(icon);
        tbExit->setIconSize(QSize(32, 32));
        tbExit->setAutoRaise(true);

        horizontalLayout_3->addWidget(tbExit);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(12);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(LoginDialog);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setPixmap(QPixmap(QString::fromUtf8(":/icon/ui/icon/logo3.png")));

        horizontalLayout_2->addWidget(label_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        leUsername = new QLineEdit(LoginDialog);
        leUsername->setObjectName(QStringLiteral("leUsername"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(leUsername->sizePolicy().hasHeightForWidth());
        leUsername->setSizePolicy(sizePolicy);
        leUsername->setMinimumSize(QSize(330, 40));
        leUsername->setMaximumSize(QSize(330, 40));
        leUsername->setStyleSheet(QStringLiteral(""));

        horizontalLayout_5->addWidget(leUsername);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        lePassword = new QLineEdit(LoginDialog);
        lePassword->setObjectName(QStringLiteral("lePassword"));
        sizePolicy.setHeightForWidth(lePassword->sizePolicy().hasHeightForWidth());
        lePassword->setSizePolicy(sizePolicy);
        lePassword->setMinimumSize(QSize(330, 40));
        lePassword->setMaximumSize(QSize(330, 40));
        lePassword->setEchoMode(QLineEdit::Password);

        horizontalLayout_6->addWidget(lePassword);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(LoginDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setOpenExternalLinks(true);

        horizontalLayout->addWidget(label);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        toolButton = new QToolButton(LoginDialog);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setAutoRaise(true);

        horizontalLayout->addWidget(toolButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setOpenExternalLinks(true);

        horizontalLayout->addWidget(label_2);


        verticalLayout->addLayout(horizontalLayout);

        tbEnterClass = new QToolButton(LoginDialog);
        tbEnterClass->setObjectName(QStringLiteral("tbEnterClass"));
        tbEnterClass->setEnabled(false);
        sizePolicy.setHeightForWidth(tbEnterClass->sizePolicy().hasHeightForWidth());
        tbEnterClass->setSizePolicy(sizePolicy);
        tbEnterClass->setMinimumSize(QSize(330, 40));
        tbEnterClass->setMaximumSize(QSize(330, 40));
        tbEnterClass->setAutoRaise(true);

        verticalLayout->addWidget(tbEnterClass);

        pbDownload = new QProgressBar(LoginDialog);
        pbDownload->setObjectName(QStringLiteral("pbDownload"));
        pbDownload->setValue(0);
        pbDownload->setAlignment(Qt::AlignCenter);
        pbDownload->setTextVisible(true);
        pbDownload->setInvertedAppearance(false);

        verticalLayout->addWidget(pbDownload);

        lbPrompt = new QLabel(LoginDialog);
        lbPrompt->setObjectName(QStringLiteral("lbPrompt"));

        verticalLayout->addWidget(lbPrompt);


        horizontalLayout_4->addLayout(verticalLayout);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer = new QSpacerItem(20, 18, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        tbExit->setText(QApplication::translate("LoginDialog", "...", 0));
        label_4->setText(QString());
        leUsername->setPlaceholderText(QApplication::translate("LoginDialog", "\350\257\267\350\276\223\345\205\245\346\202\250\347\232\204\350\264\246\345\217\267", 0));
        lePassword->setPlaceholderText(QApplication::translate("LoginDialog", "\350\257\267\350\276\223\345\205\245\346\202\250\347\232\204\345\257\206\347\240\201", 0));
        label->setText(QApplication::translate("LoginDialog", "<a  style='color: green;' href=\"http://www.k6kt.com/\">\345\277\230\350\256\260\345\257\206\347\240\201\357\274\237", 0));
        toolButton->setText(QApplication::translate("LoginDialog", "\350\257\276\347\250\213\345\233\236\346\224\276", 0));
        label_2->setText(QApplication::translate("LoginDialog", "<a style='color: green;' href=\"http://www.k6kt.com/\">\346\263\250\345\206\214\346\226\260\347\224\250\346\210\267", 0));
        tbEnterClass->setText(QApplication::translate("LoginDialog", "\350\277\233\345\205\245\350\257\276\345\240\202ff", 0));
        lbPrompt->setText(QString());
        Q_UNUSED(LoginDialog);
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
