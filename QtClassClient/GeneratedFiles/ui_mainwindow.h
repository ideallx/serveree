/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "cloginbutton.h"
#include "colorcombox.h"
#include "csettingsbutton.h"
#include "cshapechooser.h"
#include "cuserlistwidget.h"
#include "linewidthcombox.h"
#include "myview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLabel *lbLogo;
    QFrame *line;
    QToolButton *tbCourseWare;
    QFrame *line_2;
    QToolButton *tbTeacherBoard;
    QFrame *line_3;
    QToolButton *tbMyBoard;
    QFrame *line_8;
    QToolButton *tbMyClass;
    QFrame *line_7;
    LineWidthCombox *tbBrush;
    QFrame *line_4;
    CShapeChooser *tbShape;
    QFrame *line_6;
    QToolButton *tbEraser;
    QFrame *line_5;
    ColorCombox *tbPalette;
    QFrame *line_9;
    QToolButton *tbBackground;
    QFrame *line_10;
    CLoginButton *tbLogin;
    QFrame *line_11;
    CSettingsButton *tbSettings;
    QHBoxLayout *horizontalLayout_2;
    MyView *graphicsView;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout;
    QToolButton *btClassInfo;
    CUserListWidget *listWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1042, 700);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(1042, 700));
        MainWindow->setMaximumSize(QSize(1042, 510));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setMinimumSize(QSize(1024, 75));
        groupBox->setStyleSheet(QLatin1String("QGroupBox {\n"
"	border-image: url(:/back/ui/back/orange1.png);\n"
"}\n"
"Line {\n"
"	background-image: url(:/back/ui/back/line.png);\n"
"}\n"
"QToolButton:!checked {\n"
"	color: rgb(255, 255, 255);\n"
"	border:none;\n"
"}\n"
"QToolButton:checked, QToolButton:pressed { \n"
"	background-color: rgb(83, 83, 83);\n"
"}"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 0, 0, 0);
        lbLogo = new QLabel(groupBox);
        lbLogo->setObjectName(QStringLiteral("lbLogo"));
        lbLogo->setPixmap(QPixmap(QString::fromUtf8(":/icon/ui/icon/logo.png")));

        horizontalLayout->addWidget(lbLogo);

        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        tbCourseWare = new QToolButton(groupBox);
        tbCourseWare->setObjectName(QStringLiteral("tbCourseWare"));
        tbCourseWare->setMinimumSize(QSize(75, 75));
        tbCourseWare->setMaximumSize(QSize(75, 16777215));
        tbCourseWare->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/ui/icon/courseware.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbCourseWare->setIcon(icon);
        tbCourseWare->setIconSize(QSize(32, 32));
        tbCourseWare->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbCourseWare->setAutoRaise(true);

        horizontalLayout->addWidget(tbCourseWare);

        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_2);

        tbTeacherBoard = new QToolButton(groupBox);
        tbTeacherBoard->setObjectName(QStringLiteral("tbTeacherBoard"));
        tbTeacherBoard->setMinimumSize(QSize(75, 75));
        tbTeacherBoard->setMaximumSize(QSize(75, 16777215));
        tbTeacherBoard->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/ui/icon/teacher board.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbTeacherBoard->setIcon(icon1);
        tbTeacherBoard->setIconSize(QSize(32, 32));
        tbTeacherBoard->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbTeacherBoard->setAutoRaise(true);

        horizontalLayout->addWidget(tbTeacherBoard);

        line_3 = new QFrame(groupBox);
        line_3->setObjectName(QStringLiteral("line_3"));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_3);

        tbMyBoard = new QToolButton(groupBox);
        tbMyBoard->setObjectName(QStringLiteral("tbMyBoard"));
        tbMyBoard->setMinimumSize(QSize(75, 75));
        tbMyBoard->setMaximumSize(QSize(75, 16777215));
        tbMyBoard->setStyleSheet(QStringLiteral(""));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/ui/icon/my board.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbMyBoard->setIcon(icon2);
        tbMyBoard->setIconSize(QSize(32, 32));
        tbMyBoard->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbMyBoard->setAutoRaise(true);

        horizontalLayout->addWidget(tbMyBoard);

        line_8 = new QFrame(groupBox);
        line_8->setObjectName(QStringLiteral("line_8"));
        line_8->setFrameShape(QFrame::VLine);
        line_8->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_8);

        tbMyClass = new QToolButton(groupBox);
        tbMyClass->setObjectName(QStringLiteral("tbMyClass"));
        tbMyClass->setMinimumSize(QSize(75, 75));
        tbMyClass->setMaximumSize(QSize(75, 16777215));
        tbMyClass->setStyleSheet(QStringLiteral(""));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/ui/icon/my class.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbMyClass->setIcon(icon3);
        tbMyClass->setIconSize(QSize(32, 32));
        tbMyClass->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbMyClass->setAutoRaise(true);

        horizontalLayout->addWidget(tbMyClass);

        line_7 = new QFrame(groupBox);
        line_7->setObjectName(QStringLiteral("line_7"));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_7);

        tbBrush = new LineWidthCombox(groupBox);
        tbBrush->setObjectName(QStringLiteral("tbBrush"));
        tbBrush->setMinimumSize(QSize(75, 75));
        tbBrush->setMaximumSize(QSize(75, 16777215));
        tbBrush->setStyleSheet(QStringLiteral(""));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/ui/icon/brush.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbBrush->setIcon(icon4);
        tbBrush->setIconSize(QSize(32, 32));
        tbBrush->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbBrush->setAutoRaise(true);

        horizontalLayout->addWidget(tbBrush);

        line_4 = new QFrame(groupBox);
        line_4->setObjectName(QStringLiteral("line_4"));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_4);

        tbShape = new CShapeChooser(groupBox);
        tbShape->setObjectName(QStringLiteral("tbShape"));
        tbShape->setMinimumSize(QSize(75, 75));
        tbShape->setMaximumSize(QSize(75, 16777215));
        tbShape->setStyleSheet(QStringLiteral(""));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icon/ui/icon/shape.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbShape->setIcon(icon5);
        tbShape->setIconSize(QSize(32, 32));
        tbShape->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbShape->setAutoRaise(true);

        horizontalLayout->addWidget(tbShape);

        line_6 = new QFrame(groupBox);
        line_6->setObjectName(QStringLiteral("line_6"));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_6);

        tbEraser = new QToolButton(groupBox);
        tbEraser->setObjectName(QStringLiteral("tbEraser"));
        tbEraser->setMinimumSize(QSize(75, 75));
        tbEraser->setMaximumSize(QSize(75, 16777215));
        tbEraser->setStyleSheet(QStringLiteral(""));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icon/ui/icon/eraser.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbEraser->setIcon(icon6);
        tbEraser->setIconSize(QSize(32, 32));
        tbEraser->setCheckable(true);
        tbEraser->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbEraser->setAutoRaise(true);

        horizontalLayout->addWidget(tbEraser);

        line_5 = new QFrame(groupBox);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_5);

        tbPalette = new ColorCombox(groupBox);
        tbPalette->setObjectName(QStringLiteral("tbPalette"));
        tbPalette->setMinimumSize(QSize(75, 75));
        tbPalette->setMaximumSize(QSize(75, 16777215));
        tbPalette->setStyleSheet(QStringLiteral(""));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icon/ui/icon/platte.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPalette->setIcon(icon7);
        tbPalette->setIconSize(QSize(32, 32));
        tbPalette->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbPalette->setAutoRaise(true);

        horizontalLayout->addWidget(tbPalette);

        line_9 = new QFrame(groupBox);
        line_9->setObjectName(QStringLiteral("line_9"));
        line_9->setFrameShape(QFrame::VLine);
        line_9->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_9);

        tbBackground = new QToolButton(groupBox);
        tbBackground->setObjectName(QStringLiteral("tbBackground"));
        tbBackground->setMinimumSize(QSize(75, 75));
        tbBackground->setMaximumSize(QSize(75, 16777215));
        tbBackground->setStyleSheet(QStringLiteral(""));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icon/ui/icon/back ground.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbBackground->setIcon(icon8);
        tbBackground->setIconSize(QSize(32, 32));
        tbBackground->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbBackground->setAutoRaise(true);

        horizontalLayout->addWidget(tbBackground);

        line_10 = new QFrame(groupBox);
        line_10->setObjectName(QStringLiteral("line_10"));
        line_10->setFrameShape(QFrame::VLine);
        line_10->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_10);

        tbLogin = new CLoginButton(groupBox);
        tbLogin->setObjectName(QStringLiteral("tbLogin"));
        tbLogin->setMinimumSize(QSize(75, 75));
        tbLogin->setMaximumSize(QSize(75, 16777215));
        tbLogin->setStyleSheet(QStringLiteral(""));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icon/ui/icon/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbLogin->setIcon(icon9);
        tbLogin->setIconSize(QSize(32, 32));
        tbLogin->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbLogin->setAutoRaise(true);

        horizontalLayout->addWidget(tbLogin);

        line_11 = new QFrame(groupBox);
        line_11->setObjectName(QStringLiteral("line_11"));
        line_11->setFrameShape(QFrame::VLine);
        line_11->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_11);

        tbSettings = new CSettingsButton(groupBox);
        tbSettings->setObjectName(QStringLiteral("tbSettings"));
        tbSettings->setMinimumSize(QSize(30, 75));
        tbSettings->setMaximumSize(QSize(30, 16777215));
        tbSettings->setStyleSheet(QStringLiteral(""));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icon/ui/icon/manage.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbSettings->setIcon(icon10);
        tbSettings->setIconSize(QSize(32, 32));
        tbSettings->setToolButtonStyle(Qt::ToolButtonIconOnly);
        tbSettings->setAutoRaise(true);

        horizontalLayout->addWidget(tbSettings);


        verticalLayout_2->addWidget(groupBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        graphicsView = new MyView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        graphicsView->setStyleSheet(QStringLiteral("border-image: url(:/back/ui/back/background.png);"));

        horizontalLayout_2->addWidget(graphicsView);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        groupBox_2->setStyleSheet(QStringLiteral("background-color: rgb(31, 40, 49);"));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 9, 1, 0);
        btClassInfo = new QToolButton(groupBox_2);
        btClassInfo->setObjectName(QStringLiteral("btClassInfo"));
        QFont font;
        font.setFamily(QStringLiteral("Aharoni"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        btClassInfo->setFont(font);
        btClassInfo->setStyleSheet(QStringLiteral("color: rgb(82, 90, 93);"));
        btClassInfo->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btClassInfo->setAutoRaise(true);
        btClassInfo->setArrowType(Qt::NoArrow);

        verticalLayout->addWidget(btClassInfo);

        listWidget = new CUserListWidget(groupBox_2);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(27, 36, 45);\n"
"padding-left: 20px;\n"
"padding-right: 20px;\n"
"alternate-background-color: yellow;"));
        listWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        listWidget->setViewMode(QListView::ListMode);

        verticalLayout->addWidget(listWidget);


        horizontalLayout_2->addWidget(groupBox_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        groupBox->setTitle(QString());
        lbLogo->setText(QString());
        tbCourseWare->setText(QApplication::translate("MainWindow", "\346\225\231\345\270\210\350\257\276\344\273\266", 0));
        tbTeacherBoard->setText(QApplication::translate("MainWindow", "\346\225\231\345\270\210\347\231\275\346\235\277", 0));
        tbMyBoard->setText(QApplication::translate("MainWindow", "\346\210\221\347\232\204\347\231\275\346\235\277", 0));
        tbMyClass->setText(QApplication::translate("MainWindow", "\346\210\221\347\232\204\347\217\255\347\272\247", 0));
        tbBrush->setText(QApplication::translate("MainWindow", "\347\224\273\347\254\224", 0));
        tbShape->setText(QApplication::translate("MainWindow", "\345\233\276\345\275\242", 0));
        tbEraser->setText(QApplication::translate("MainWindow", "\346\251\241\347\232\256\346\223\246", 0));
        tbPalette->setText(QApplication::translate("MainWindow", "\350\260\203\350\211\262\346\235\277", 0));
        tbBackground->setText(QApplication::translate("MainWindow", "\350\203\214\346\231\257\347\261\273\345\236\213", 0));
        tbLogin->setText(QApplication::translate("MainWindow", "\347\231\273\345\275\225", 0));
        tbSettings->setText(QString());
        groupBox_2->setTitle(QString());
        btClassInfo->setText(QApplication::translate("MainWindow", "         CONTACT LIST                  X    ", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
