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
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_5;
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
    CourseWareWidget *wgtCourse;
    MyView *graphicsView;
    QGroupBox *groupBox_2;
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
        MainWindow->setStyleSheet(QLatin1String("QListView {\n"
"	color: rgb(255, 255, 255);\n"
"	background-color: rgb(45, 55, 64);\n"
"	padding-left: 20px;\n"
"	padding-right: 20px;\n"
"	border:none\n"
"}\n"
"\n"
"QListView::item:selected, QListView::item:hover{\n"
"	background: rgb(66, 79, 88);\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QGroupBox {\n"
"	background-color: rgb(31, 40, 49);\n"
"	border: none;\n"
"}\n"
"\n"
"QGroupBox#gbWareCtrl {\n"
"	background-color: rgb(66, 79, 88);\n"
"}\n"
"\n"
"QGroupBox {\n"
"	background-color: rgb(31, 40, 49);\n"
"	border: none;\n"
"}\n"
"\n"
"QToolButton {\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"MyView {\n"
"	background-color: rgb(255, 254, 240);\n"
"}\n"
"\n"
"QLabel {\n"
"	color: white;\n"
"}\n"
"\n"
"QListWidget:item {\n"
"	height: 33;\n"
"}\n"
"\n"
"QScrollBar:vertical {\n"
"	border-radius: 5px;\n"
"    background: rgb(69, 77, 80);\n"
"    width: 12px;\n"
"    margin: 22px 0 22px 0;\n"
"}\n"
"QScrollBar::handle:vertical {\n"
"	border-radius: 5px;\n"
"    background: rgb(26, 29, 34);\n"
"    min-height"
                        ": 20px;\n"
"}\n"
"QScrollBar::add-line:vertical {\n"
"	border-radius: 5px;\n"
"    background: rgb(45, 55, 64);\n"
"    height: 20px;\n"
"    subcontrol-position: bottom;\n"
"    subcontrol-origin: margin;\n"
"}\n"
"\n"
"QScrollBar::sub-line:vertical {\n"
"	border-radius: 5px;\n"
"    background: rgb(45, 55, 64);\n"
"    height: 20px;\n"
"    subcontrol-position: top;\n"
"    subcontrol-origin: margin;\n"
"}\n"
"QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {\n"
"	border-radius: 5px;\n"
"    width: 3px;\n"
"    height: 3px;\n"
"    background: white;\n"
"}\n"
"\n"
"QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {\n"
"	border-radius: 5px;\n"
"    background: none;\n"
"}\n"
""));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(1024, 75));
        groupBox->setMaximumSize(QSize(16777215, 75));
        groupBox->setStyleSheet(QLatin1String("QGroupBox {\n"
"	border-image: url(:/back/ui/back/orange1.png);\n"
"	border:none;\n"
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
"	border:none;\n"
"}"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(9, 0, 0, 0);
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        lbLogo = new QLabel(groupBox);
        lbLogo->setObjectName(QStringLiteral("lbLogo"));
        lbLogo->setMinimumSize(QSize(480, 0));
        lbLogo->setMaximumSize(QSize(480, 16777215));
        lbLogo->setPixmap(QPixmap(QString::fromUtf8(":/icon/ui/icon/fulann_logo.png")));

        horizontalLayout->addWidget(lbLogo);

        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        tbCourseWare = new QToolButton(groupBox);
        tbCourseWare->setObjectName(QStringLiteral("tbCourseWare"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tbCourseWare->sizePolicy().hasHeightForWidth());
        tbCourseWare->setSizePolicy(sizePolicy2);
        tbCourseWare->setMinimumSize(QSize(75, 75));
        tbCourseWare->setMaximumSize(QSize(16777215, 16777215));
        tbCourseWare->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/ui/icon/courseware.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbCourseWare->setIcon(icon1);
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
        sizePolicy2.setHeightForWidth(tbTeacherBoard->sizePolicy().hasHeightForWidth());
        tbTeacherBoard->setSizePolicy(sizePolicy2);
        tbTeacherBoard->setMinimumSize(QSize(75, 75));
        tbTeacherBoard->setMaximumSize(QSize(16777215, 16777215));
        tbTeacherBoard->setStyleSheet(QStringLiteral(""));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/ui/icon/teacher board.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbTeacherBoard->setIcon(icon2);
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
        sizePolicy2.setHeightForWidth(tbMyBoard->sizePolicy().hasHeightForWidth());
        tbMyBoard->setSizePolicy(sizePolicy2);
        tbMyBoard->setMinimumSize(QSize(75, 75));
        tbMyBoard->setMaximumSize(QSize(16777215, 16777215));
        tbMyBoard->setStyleSheet(QStringLiteral(""));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/icon/ui/icon/my board.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbMyBoard->setIcon(icon3);
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
        sizePolicy2.setHeightForWidth(tbMyClass->sizePolicy().hasHeightForWidth());
        tbMyClass->setSizePolicy(sizePolicy2);
        tbMyClass->setMinimumSize(QSize(75, 75));
        tbMyClass->setMaximumSize(QSize(16777215, 16777215));
        tbMyClass->setStyleSheet(QStringLiteral(""));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/icon/ui/icon/my class.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbMyClass->setIcon(icon4);
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
        sizePolicy2.setHeightForWidth(tbBrush->sizePolicy().hasHeightForWidth());
        tbBrush->setSizePolicy(sizePolicy2);
        tbBrush->setMinimumSize(QSize(75, 75));
        tbBrush->setMaximumSize(QSize(16777215, 16777215));
        tbBrush->setStyleSheet(QStringLiteral(""));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/icon/ui/icon/brush.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbBrush->setIcon(icon5);
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
        sizePolicy2.setHeightForWidth(tbShape->sizePolicy().hasHeightForWidth());
        tbShape->setSizePolicy(sizePolicy2);
        tbShape->setMinimumSize(QSize(75, 75));
        tbShape->setMaximumSize(QSize(16777215, 16777215));
        tbShape->setStyleSheet(QStringLiteral(""));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/icon/ui/icon/shape.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbShape->setIcon(icon6);
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
        sizePolicy2.setHeightForWidth(tbEraser->sizePolicy().hasHeightForWidth());
        tbEraser->setSizePolicy(sizePolicy2);
        tbEraser->setMinimumSize(QSize(75, 75));
        tbEraser->setMaximumSize(QSize(16777215, 16777215));
        tbEraser->setStyleSheet(QStringLiteral(""));
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/icon/ui/icon/eraser.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbEraser->setIcon(icon7);
        tbEraser->setIconSize(QSize(32, 32));
        tbEraser->setCheckable(true);
        tbEraser->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tbEraser->setAutoRaise(true);
        tbEraser->setArrowType(Qt::NoArrow);

        horizontalLayout->addWidget(tbEraser);

        line_5 = new QFrame(groupBox);
        line_5->setObjectName(QStringLiteral("line_5"));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line_5);

        tbPalette = new ColorCombox(groupBox);
        tbPalette->setObjectName(QStringLiteral("tbPalette"));
        sizePolicy2.setHeightForWidth(tbPalette->sizePolicy().hasHeightForWidth());
        tbPalette->setSizePolicy(sizePolicy2);
        tbPalette->setMinimumSize(QSize(75, 75));
        tbPalette->setMaximumSize(QSize(16777215, 16777215));
        tbPalette->setStyleSheet(QStringLiteral(""));
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/icon/ui/icon/platte.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPalette->setIcon(icon8);
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
        sizePolicy2.setHeightForWidth(tbBackground->sizePolicy().hasHeightForWidth());
        tbBackground->setSizePolicy(sizePolicy2);
        tbBackground->setMinimumSize(QSize(75, 75));
        tbBackground->setMaximumSize(QSize(16777215, 16777215));
        tbBackground->setStyleSheet(QStringLiteral(""));
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/icon/ui/icon/back ground.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbBackground->setIcon(icon9);
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
        sizePolicy2.setHeightForWidth(tbLogin->sizePolicy().hasHeightForWidth());
        tbLogin->setSizePolicy(sizePolicy2);
        tbLogin->setMinimumSize(QSize(75, 75));
        tbLogin->setMaximumSize(QSize(16777215, 16777215));
        tbLogin->setStyleSheet(QStringLiteral(""));
        QIcon icon10;
        icon10.addFile(QStringLiteral(":/icon/ui/icon/user.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbLogin->setIcon(icon10);
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
        tbSettings->setMinimumSize(QSize(60, 75));
        tbSettings->setMaximumSize(QSize(30, 16777215));
        tbSettings->setStyleSheet(QStringLiteral(""));
        QIcon icon11;
        icon11.addFile(QStringLiteral(":/icon/ui/icon/manage.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbSettings->setIcon(icon11);
        tbSettings->setIconSize(QSize(32, 32));
        tbSettings->setToolButtonStyle(Qt::ToolButtonIconOnly);
        tbSettings->setAutoRaise(true);

        horizontalLayout->addWidget(tbSettings);


        verticalLayout_2->addWidget(groupBox);

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

        horizontalLayout_2->addWidget(graphicsView);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy3);
        groupBox_2->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(groupBox_2);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(1, 9, 1, 0);
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setPointSize(12);
        label_2->setFont(font);

        horizontalLayout_6->addWidget(label_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_2);

        btClassInfo = new QToolButton(groupBox_2);
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

        listWidget = new CUserListWidget(groupBox_2);
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


        horizontalLayout_2->addWidget(groupBox_2);


        verticalLayout_2->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\344\272\222\345\212\250\350\257\276\345\240\202", 0));
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
        label_2->setText(QApplication::translate("MainWindow", "\350\201\224\347\263\273\344\272\272\345\210\227\350\241\250", 0));
        btClassInfo->setText(QApplication::translate("MainWindow", "   X   ", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
