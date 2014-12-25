/********************************************************************************
** Form generated from reading UI file 'dialogpixmap.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOGPIXMAP_H
#define UI_DIALOGPIXMAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QToolButton>

QT_BEGIN_NAMESPACE

class Ui_DialogPixmap
{
public:
    QToolButton *toolButton;

    void setupUi(QDialog *DialogPixmap)
    {
        if (DialogPixmap->objectName().isEmpty())
            DialogPixmap->setObjectName(QStringLiteral("DialogPixmap"));
        DialogPixmap->resize(379, 166);
        DialogPixmap->setStyleSheet(QLatin1String("QDialog {\n"
"	background-image: url(:/back/ui/back/backRace.png);\n"
"}\n"
"\n"
"QToolButton {\n"
"	border: none;\n"
"	background-image: url(:/icon/ui/icon/raceUp.png);\n"
"}\n"
"\n"
"QToolButton::pressed {\n"
"	background-image: url(:/icon/ui/icon/raceDown.png);\n"
"}"));
        toolButton = new QToolButton(DialogPixmap);
        toolButton->setObjectName(QStringLiteral("toolButton"));
        toolButton->setGeometry(QRect(93, 36, 191, 91));
        toolButton->setAutoRaise(true);

        retranslateUi(DialogPixmap);

        QMetaObject::connectSlotsByName(DialogPixmap);
    } // setupUi

    void retranslateUi(QDialog *DialogPixmap)
    {
        DialogPixmap->setWindowTitle(QApplication::translate("DialogPixmap", "Dialog", 0));
        toolButton->setText(QApplication::translate("DialogPixmap", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class DialogPixmap: public Ui_DialogPixmap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOGPIXMAP_H
