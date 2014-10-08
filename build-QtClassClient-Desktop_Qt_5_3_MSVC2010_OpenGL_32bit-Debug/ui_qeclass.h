/********************************************************************************
** Form generated from reading UI file 'qeclass.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QECLASS_H
#define UI_QECLASS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include "ipaddresswidget.h"

QT_BEGIN_NAMESPACE

class Ui_QEClass
{
public:
    QLineEdit *EDT_PASSWORD;
    QLineEdit *EDT_USERNAME;
    QToolButton *BTN_LOGIN;
    IpAddressWidget *widget;

    void setupUi(QDialog *QEClass)
    {
        if (QEClass->objectName().isEmpty())
            QEClass->setObjectName(QStringLiteral("QEClass"));
        QEClass->resize(325, 513);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(QEClass->sizePolicy().hasHeightForWidth());
        QEClass->setSizePolicy(sizePolicy);
        QEClass->setMaximumSize(QSize(1920, 1080));
        QEClass->setMouseTracking(true);
        QEClass->setWindowOpacity(1);
        QEClass->setStyleSheet(QStringLiteral("QDialog{border-image: url(:/EClassPic/EClassPic/login_background.png)}"));
        EDT_PASSWORD = new QLineEdit(QEClass);
        EDT_PASSWORD->setObjectName(QStringLiteral("EDT_PASSWORD"));
        EDT_PASSWORD->setGeometry(QRect(20, 310, 291, 51));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(EDT_PASSWORD->sizePolicy().hasHeightForWidth());
        EDT_PASSWORD->setSizePolicy(sizePolicy1);
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        EDT_PASSWORD->setFont(font);
        EDT_PASSWORD->setEchoMode(QLineEdit::Password);
        EDT_PASSWORD->setAlignment(Qt::AlignCenter);
        EDT_PASSWORD->setClearButtonEnabled(true);
        EDT_USERNAME = new QLineEdit(QEClass);
        EDT_USERNAME->setObjectName(QStringLiteral("EDT_USERNAME"));
        EDT_USERNAME->setEnabled(true);
        EDT_USERNAME->setGeometry(QRect(20, 250, 291, 50));
        sizePolicy1.setHeightForWidth(EDT_USERNAME->sizePolicy().hasHeightForWidth());
        EDT_USERNAME->setSizePolicy(sizePolicy1);
        EDT_USERNAME->setFont(font);
        EDT_USERNAME->setToolTipDuration(-1);
        EDT_USERNAME->setAlignment(Qt::AlignCenter);
        EDT_USERNAME->setCursorMoveStyle(Qt::LogicalMoveStyle);
        EDT_USERNAME->setClearButtonEnabled(true);
        BTN_LOGIN = new QToolButton(QEClass);
        BTN_LOGIN->setObjectName(QStringLiteral("BTN_LOGIN"));
        BTN_LOGIN->setGeometry(QRect(0, 450, 325, 61));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        BTN_LOGIN->setFont(font1);
        BTN_LOGIN->setStyleSheet(QStringLiteral(""));
        widget = new IpAddressWidget(QEClass);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(-10, 370, 350, 61));
        QWidget::setTabOrder(EDT_USERNAME, EDT_PASSWORD);
        QWidget::setTabOrder(EDT_PASSWORD, BTN_LOGIN);

        retranslateUi(QEClass);
        QObject::connect(BTN_LOGIN, SIGNAL(clicked()), QEClass, SLOT(accept()));

        QMetaObject::connectSlotsByName(QEClass);
    } // setupUi

    void retranslateUi(QDialog *QEClass)
    {
        QEClass->setWindowTitle(QApplication::translate("QEClass", "QEClass", 0));
        EDT_PASSWORD->setPlaceholderText(QApplication::translate("QEClass", "\345\257\206\347\240\201", 0));
#ifndef QT_NO_TOOLTIP
        EDT_USERNAME->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        EDT_USERNAME->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        EDT_USERNAME->setText(QString());
        EDT_USERNAME->setPlaceholderText(QApplication::translate("QEClass", "\347\224\250\346\210\267\345\220\215", 0));
        BTN_LOGIN->setText(QApplication::translate("QEClass", "\347\231\273\351\231\206", 0));
    } // retranslateUi

};

namespace Ui {
    class QEClass: public Ui_QEClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QECLASS_H
