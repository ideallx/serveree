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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "cloginbutton.h"
#include "colorcombox.h"
#include "coursewarewidget.h"
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
    QGroupBox *gbCommandbar;
    QHBoxLayout *horizontalLayout;
    QLabel *lbLogo;
    QToolButton *tbQuestion;
    QToolButton *tbCourseWare;
    QToolButton *tbTeacherBoard;
    QToolButton *tbMyBoard;
    LineWidthCombox *tbBrush;
    ColorCombox *tbPalette;
    CShapeChooser *tbShape;
    QToolButton *tbEraser;
    QToolButton *tbBackground;
    QToolButton *tbMyClass;
    CLoginButton *tbLogin;
    CSettingsButton *tbSettings;
    QHBoxLayout *horizontalLayout_2;
    CourseWareWidget *wgtCourse;
    MyView *graphicsView;
    QGroupBox *gbUserlist;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QToolButton *btClassInfo;
    CUserListWidget *listWidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1042, 700);
        MainWindow->setMinimumSize(QSize(1042, 700));
        MainWindow->setMaximumSize(QSize(1042, 510));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/ui/icon/fulann_logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        gbCommandbar = new QGroupBox(centralWidget);
        gbCommandbar->setObjectName(QStringLiteral("gbCommandbar"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gbCommandbar->sizePolicy().hasHeightForWidth());
        gbCommandbar->setSizePolicy(sizePolicy1);
        gbCommandbar->setMinimumSize(QSize(1024, 75));
        gbCommandbar->setMaximumSize(QSize(16777215, 75));
        gbCommandbar->setStyleSheet(QStringLiteral(""));
        horizontalLayout = new QHBoxLayout(gbCommandbar);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 0, 0, 0);
        lbLogo = new QLabel(gbCommandbar);
        lbLogo->setObjectName(QStringLiteral("lbLogo"));
        lbLogo->setMinimumSize(QSize(0, 0));
        lbLogo->setMaximumSize(QSize(16777215, 16777215));
        lbLogo->setStyleSheet(QLatin1String("QToolButton#tbCourseWare {\n"
"	border-style: outset;\n"
"	border-top-width: 4px;\n"
"	border-top-color: rgb(233, 71, 7);\n"
"};"));
        lbLogo->setPixmap(QPixmap(QString::fromUtf8(":/icon/ui/icon/logo icon.png")));
        lbLogo->setScaledContents(false);
        lbLogo->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(lbLogo);

        tbQuestion = new QToolButton(gbCommandbar);
        tbQuestion->setObjectName(QStringLiteral("tbQuestion"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tbQuestion->sizePolicy().hasHeightForWidth());
        tbQuestion->setSizePolicy(sizePolicy2);
        tbQuestion->setMinimumSize(QSize(75, 75));
        tbQuestion->setMaximumSize(QSize(120, 16777215));
        tbQuestion->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/ui/icon/question.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbQuestion->setIcon(icon1);
        tbQuestion->setIconSize(QSize(32, 32));
        tbQuestion->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbQuestion->setAutoRaise(true);

        horizontalLayout->addWidget(tbQuestion);

        tbCourseWare = new QToolButton(gbCommandbar);
        tbCourseWare->setObjectName(QStringLiteral("tbCourseWare"));
        sizePolicy2.setHeightForWidth(tbCourseWare->sizePolicy().hasHeightForWidth());
        tbCourseWare->setSizePolicy(sizePolicy2);
        tbCourseWare->setMinimumSize(QSize(75, 75));
        tbCourseWare->setMaximumSize(QSize(120, 16777215));
        tbCourseWare->setStyleSheet(QStringLiteral(""));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/ui/icon/courseware.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbCourseWare->setIcon(icon2);
        tbCourseWare->setIconSize(QSize(32, 32));
        tbCourseWare->setCheckable(true);
        tbCourseWare->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbCourseWare->setAutoRaise(true);

        horizontalLayout->addWidget(tbCourseWare);

        tbTeacherBoard = new QToolButton(gbCommandbar);
        tbTeacherBoard->setObjectName(QStringLiteral("tbTeacherBoard"));
        sizePolicy2.setHeightForWidth(tbTeacherBoard->sizePolicy().hasHeightForWidth());
        tbTeacherBoard->setSizePolicy(sizePolicy2);
        tbTeacherBoard->setMinimumSize(QSize(75, 75));
        tbTeacherBoard->setMaximumSize(QSize(120, 16777215));
        tbTeacherBoard->setStyleSheet(QStringLiteral(""));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/ui/icon/teacher board.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbTeacherBoard->setIcon(icon3);
        tbTeacherBoard->setIconSize(QSize(32, 32));
        tbTeacherBoard->setCheckable(true);
        tbTeacherBoard->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbTeacherBoard->setAutoRaise(true);

        horizontalLayout->addWidget(tbTeacherBoard);

        tbMyBoard = new QToolButton(gbCommandbar);
        tbMyBoard->setObjectName(QStringLiteral("tbMyBoard"));
        sizePolicy2.setHeightForWidth(tbMyBoard->sizePolicy().hasHeightForWidth());
        tbMyBoard->setSizePolicy(sizePolicy2);
        tbMyBoard->setMinimumSize(QSize(75, 75));
        tbMyBoard->setMaximumSize(QSize(120, 16777215));
        tbMyBoard->setStyleSheet(QStringLiteral(""));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/ui/icon/my board.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbMyBoard->setIcon(icon4);
        tbMyBoard->setIconSize(QSize(32, 32));
        tbMyBoard->setCheckable(true);
        tbMyBoard->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbMyBoard->setAutoRaise(true);

        horizontalLayout->addWidget(tbMyBoard);

        tbBrush = new LineWidthCombox(gbCommandbar);
        tbBrush->setObjectName(QStringLiteral("tbBrush"));
        sizePolicy2.setHeightForWidth(tbBrush->sizePolicy().hasHeightForWidth());
        tbBrush->setSizePolicy(sizePolicy2);
        tbBrush->setMinimumSize(QSize(75, 75));
        tbBrush->setMaximumSize(QSize(120, 16777215));
        tbBrush->setStyleSheet(QStringLiteral(""));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icon/ui/icon/brush.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbBrush->setIcon(icon5);
        tbBrush->setIconSize(QSize(32, 32));
        tbBrush->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbBrush->setAutoRaise(true);

        horizontalLayout->addWidget(tbBrush);

        tbPalette = new ColorCombox(gbCommandbar);
        tbPalette->setObjectName(QStringLiteral("tbPalette"));
        sizePolicy2.setHeightForWidth(tbPalette->sizePolicy().hasHeightForWidth());
        tbPalette->setSizePolicy(sizePolicy2);
        tbPalette->setMinimumSize(QSize(75, 75));
        tbPalette->setMaximumSize(QSize(120, 16777215));
        tbPalette->setStyleSheet(QStringLiteral(""));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icon/ui/icon/platte.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPalette->setIcon(icon6);
        tbPalette->setIconSize(QSize(32, 32));
        tbPalette->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbPalette->setAutoRaise(true);

        horizontalLayout->addWidget(tbPalette);

        tbShape = new CShapeChooser(gbCommandbar);
        tbShape->setObjectName(QStringLiteral("tbShape"));
        sizePolicy2.setHeightForWidth(tbShape->sizePolicy().hasHeightForWidth());
        tbShape->setSizePolicy(sizePolicy2);
        tbShape->setMinimumSize(QSize(75, 75));
        tbShape->setMaximumSize(QSize(120, 16777215));
        tbShape->setStyleSheet(QStringLiteral(""));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icon/ui/icon/shape.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbShape->setIcon(icon7);
        tbShape->setIconSize(QSize(32, 32));
        tbShape->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbShape->setAutoRaise(true);

        horizontalLayout->addWidget(tbShape);

        tbEraser = new QToolButton(gbCommandbar);
        tbEraser->setObjectName(QStringLiteral("tbEraser"));
        sizePolicy2.setHeightForWidth(tbEraser->sizePolicy().hasHeightForWidth());
        tbEraser->setSizePolicy(sizePolicy2);
        tbEraser->setMinimumSize(QSize(75, 75));
        tbEraser->setMaximumSize(QSize(120, 16777215));
        tbEraser->setStyleSheet(QStringLiteral(""));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icon/ui/icon/eraser.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbEraser->setIcon(icon8);
        tbEraser->setIconSize(QSize(32, 32));
        tbEraser->setCheckable(true);
        tbEraser->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbEraser->setAutoRaise(true);
        tbEraser->setArrowType(Qt::NoArrow);

        horizontalLayout->addWidget(tbEraser);

        tbBackground = new QToolButton(gbCommandbar);
        tbBackground->setObjectName(QStringLiteral("tbBackground"));
        sizePolicy2.setHeightForWidth(tbBackground->sizePolicy().hasHeightForWidth());
        tbBackground->setSizePolicy(sizePolicy2);
        tbBackground->setMinimumSize(QSize(75, 75));
        tbBackground->setMaximumSize(QSize(120, 16777215));
        tbBackground->setStyleSheet(QStringLiteral(""));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icon/ui/icon/back ground.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbBackground->setIcon(icon9);
        tbBackground->setIconSize(QSize(32, 32));
        tbBackground->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbBackground->setAutoRaise(true);

        horizontalLayout->addWidget(tbBackground);

        tbMyClass = new QToolButton(gbCommandbar);
        tbMyClass->setObjectName(QStringLiteral("tbMyClass"));
        sizePolicy2.setHeightForWidth(tbMyClass->sizePolicy().hasHeightForWidth());
        tbMyClass->setSizePolicy(sizePolicy2);
        tbMyClass->setMinimumSize(QSize(75, 75));
        tbMyClass->setMaximumSize(QSize(120, 16777215));
        tbMyClass->setStyleSheet(QStringLiteral(""));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icon/ui/icon/my class.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbMyClass->setIcon(icon10);
        tbMyClass->setIconSize(QSize(32, 32));
        tbMyClass->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbMyClass->setAutoRaise(true);

        horizontalLayout->addWidget(tbMyClass);

        tbLogin = new CLoginButton(gbCommandbar);
        tbLogin->setObjectName(QStringLiteral("tbLogin"));
        sizePolicy2.setHeightForWidth(tbLogin->sizePolicy().hasHeightForWidth());
        tbLogin->setSizePolicy(sizePolicy2);
        tbLogin->setMinimumSize(QSize(75, 75));
        tbLogin->setMaximumSize(QSize(120, 16777215));
        tbLogin->setStyleSheet(QStringLiteral(""));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icon/ui/icon/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbLogin->setIcon(icon11);
        tbLogin->setIconSize(QSize(32, 32));
        tbLogin->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbLogin->setAutoRaise(true);

        horizontalLayout->addWidget(tbLogin);

        tbSettings = new CSettingsButton(gbCommandbar);
        tbSettings->setObjectName(QStringLiteral("tbSettings"));
        tbSettings->setMinimumSize(QSize(60, 75));
        tbSettings->setMaximumSize(QSize(30, 16777215));
        tbSettings->setStyleSheet(QStringLiteral(""));
        QIcon icon12;
        icon12.addFile(QStringLiteral(":/icon/ui/icon/manage.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbSettings->setIcon(icon12);
        tbSettings->setIconSize(QSize(32, 32));
        tbSettings->setToolButtonStyle(Qt::ToolButtonIconOnly);
        tbSettings->setAutoRaise(true);

        horizontalLayout->addWidget(tbSettings);


        verticalLayout_2->addWidget(gbCommandbar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        wgtCourse = new CourseWareWidget(centralWidget);
        wgtCourse->setObjectName(QStringLiteral("wgtCourse"));

        horizontalLayout_2->addWidget(wgtCourse);

        graphicsView = new MyView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        graphicsView->setStyleSheet(QStringLiteral(""));
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        graphicsView->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);

        horizontalLayout_2->addWidget(graphicsView);

        gbUserlist = new QGroupBox(centralWidget);
        gbUserlist->setObjectName(QStringLiteral("gbUserlist"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(gbUserlist->sizePolicy().hasHeightForWidth());
        gbUserlist->setSizePolicy(sizePolicy3);
        gbUserlist->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(gbUserlist);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 9, 1, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        label_2 = new QLabel(gbUserlist);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setPointSize(12);
        label_2->setFont(font);

        horizontalLayout_6->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        btClassInfo = new QToolButton(gbUserlist);
        btClassInfo->setObjectName(QStringLiteral("btClassInfo"));
        QFont font1;
        font1.setFamily(QStringLiteral("Aharoni"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        btClassInfo->setFont(font1);
        btClassInfo->setStyleSheet(QStringLiteral(""));
        btClassInfo->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        btClassInfo->setAutoRaise(true);
        btClassInfo->setArrowType(Qt::NoArrow);

        horizontalLayout_6->addWidget(btClassInfo);


        verticalLayout->addLayout(horizontalLayout_6);

        listWidget = new CUserListWidget(gbUserlist);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QFont font2;
        font2.setPointSize(10);
        listWidget->setFont(font2);
        listWidget->setStyleSheet(QStringLiteral(""));
        listWidget->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        listWidget->setGridSize(QSize(0, 36));
        listWidget->setViewMode(QListView::ListMode);
        listWidget->setUniformItemSizes(true);

        verticalLayout->addWidget(listWidget);


        horizontalLayout_2->addWidget(gbUserlist);


        verticalLayout_2->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\344\272\222\345\212\250\350\257\276\345\240\202", 0));
        gbCommandbar->setTitle(QString());
        lbLogo->setText(QString());
        tbQuestion->setText(QApplication::translate("MainWindow", "\350\257\276\345\240\202\347\255\224\351\242\230", 0));
        tbCourseWare->setText(QApplication::translate("MainWindow", "\346\225\231\345\270\210\350\257\276\344\273\266", 0));
        tbTeacherBoard->setText(QApplication::translate("MainWindow", "\346\225\231\345\270\210\347\231\275\346\235\277", 0));
        tbMyBoard->setText(QApplication::translate("MainWindow", "\346\210\221\347\232\204\347\231\275\346\235\277", 0));
        tbBrush->setText(QApplication::translate("MainWindow", "\347\224\273\347\254\224", 0));
        tbPalette->setText(QApplication::translate("MainWindow", "\350\260\203\350\211\262\346\235\277", 0));
        tbShape->setText(QApplication::translate("MainWindow", "\345\233\276\345\275\242", 0));
        tbEraser->setText(QApplication::translate("MainWindow", "\346\251\241\347\232\256\346\223\246", 0));
        tbBackground->setText(QApplication::translate("MainWindow", "\350\203\214\346\231\257\347\261\273\345\236\213", 0));
        tbMyClass->setText(QApplication::translate("MainWindow", "\346\210\221\347\232\204\347\217\255\347\272\247", 0));
        tbLogin->setText(QApplication::translate("MainWindow", "\347\231\273\345\275\225", 0));
        tbSettings->setText(QString());
        gbUserlist->setTitle(QString());
        label_2->setText(QApplication::translate("MainWindow", "\350\201\224\347\263\273\344\272\272\345\210\227\350\241\250", 0));
        btClassInfo->setText(QApplication::translate("MainWindow", "   X   ", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
