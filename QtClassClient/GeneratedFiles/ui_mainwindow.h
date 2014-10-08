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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "colorcombox.h"
#include "linewidthcombox.h"
#include "myview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionEnterClass;
    QAction *actionLeaveClass;
    QAction *actionClearScreen;
    QAction *actionExit;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *listWidget;
    QVBoxLayout *verticalLayout;
    MyView *graphicsView;
    QLabel *label;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QHBoxLayout *horizontalLayout;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer;
    LineWidthCombox *comboxPenWidth;
    QSpacerItem *horizontalSpacer_2;
    ColorCombox *ComboxPenColor;
    QSpacerItem *horizontalSpacer_3;
    ColorCombox *ComboxBrushColor;
    QStatusBar *statusBar;
    QToolBar *mainToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->setWindowModality(Qt::WindowModal);
        MainWindow->resize(1027, 811);
        QIcon icon;
        icon.addFile(QStringLiteral(":/EClassPic/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(42, 41, 57);"));
        actionEnterClass = new QAction(MainWindow);
        actionEnterClass->setObjectName(QStringLiteral("actionEnterClass"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/EClassPic/EClassPic/enterclass1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEnterClass->setIcon(icon1);
        actionLeaveClass = new QAction(MainWindow);
        actionLeaveClass->setObjectName(QStringLiteral("actionLeaveClass"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/EClassPic/EClassPic/leaveclass1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLeaveClass->setIcon(icon2);
        actionLeaveClass->setVisible(false);
        actionClearScreen = new QAction(MainWindow);
        actionClearScreen->setObjectName(QStringLiteral("actionClearScreen"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/EClassPic/EClassPic/clearscreen1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClearScreen->setIcon(icon3);
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/EClassPic/EClassPic/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon4);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout_2 = new QHBoxLayout(centralWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        listWidget = new QListWidget(centralWidget);
        QListWidgetItem *__qlistwidgetitem = new QListWidgetItem(listWidget);
        __qlistwidgetitem->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/EClassPic/EClassPic/QQ.png"), QSize(), QIcon::Normal, QIcon::Off);
        QListWidgetItem *__qlistwidgetitem1 = new QListWidgetItem(listWidget);
        __qlistwidgetitem1->setIcon(icon5);
        QListWidgetItem *__qlistwidgetitem2 = new QListWidgetItem(listWidget);
        __qlistwidgetitem2->setIcon(icon5);
        QListWidgetItem *__qlistwidgetitem3 = new QListWidgetItem(listWidget);
        __qlistwidgetitem3->setIcon(icon5);
        QListWidgetItem *__qlistwidgetitem4 = new QListWidgetItem(listWidget);
        __qlistwidgetitem4->setIcon(icon5);
        QListWidgetItem *__qlistwidgetitem5 = new QListWidgetItem(listWidget);
        __qlistwidgetitem5->setIcon(icon5);
        QListWidgetItem *__qlistwidgetitem6 = new QListWidgetItem(listWidget);
        __qlistwidgetitem6->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled);
        QListWidgetItem *__qlistwidgetitem7 = new QListWidgetItem(listWidget);
        __qlistwidgetitem7->setIcon(icon5);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy);
        listWidget->setMaximumSize(QSize(200, 16777215));
        listWidget->setStyleSheet(QStringLiteral("background-color: rgb(240, 240, 240);"));

        horizontalLayout_2->addWidget(listWidget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        graphicsView = new MyView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->viewport()->setProperty("cursor", QVariant(QCursor(Qt::CrossCursor)));
        graphicsView->setStyleSheet(QStringLiteral("border-image: url(:/EClassPic/EClassPic/back3.jpg);"));

        verticalLayout->addWidget(graphicsView);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Aharoni"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("color: rgb(133, 233, 255);\n"
"color: rgb(222, 222, 222);"));

        verticalLayout->addWidget(label);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 799, 325));
        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        comboBox = new QComboBox(centralWidget);
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/EClassPic/EClassPic/poly.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon6, QString());
        QIcon icon7;
        icon7.addFile(QStringLiteral(":/EClassPic/EClassPic/line.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon7, QString());
        QIcon icon8;
        icon8.addFile(QStringLiteral(":/EClassPic/EClassPic/rectangle.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon8, QString());
        QIcon icon9;
        icon9.addFile(QStringLiteral(":/EClassPic/EClassPic/ellipse.png"), QSize(), QIcon::Normal, QIcon::Off);
        comboBox->addItem(icon9, QString());
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setStyleSheet(QStringLiteral("color: rgb(222, 222, 222);"));
        comboBox->setIconSize(QSize(100, 30));

        horizontalLayout->addWidget(comboBox);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        comboxPenWidth = new LineWidthCombox(centralWidget);
        comboxPenWidth->setObjectName(QStringLiteral("comboxPenWidth"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(comboxPenWidth->sizePolicy().hasHeightForWidth());
        comboxPenWidth->setSizePolicy(sizePolicy1);
        comboxPenWidth->setMinimumSize(QSize(105, 32));
        comboxPenWidth->setMaximumSize(QSize(105, 32));
        comboxPenWidth->setStyleSheet(QStringLiteral("border-image: url(:/EClassPic/EClassPic/penwidth1.png);"));

        horizontalLayout->addWidget(comboxPenWidth);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        ComboxPenColor = new ColorCombox(centralWidget);
        ComboxPenColor->setObjectName(QStringLiteral("ComboxPenColor"));
        QSizePolicy sizePolicy2(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(ComboxPenColor->sizePolicy().hasHeightForWidth());
        ComboxPenColor->setSizePolicy(sizePolicy2);
        ComboxPenColor->setMinimumSize(QSize(105, 32));
        ComboxPenColor->setMaximumSize(QSize(105, 32));
        ComboxPenColor->setStyleSheet(QStringLiteral("border-image: url(:/EClassPic/EClassPic/pencolor1.png);"));

        horizontalLayout->addWidget(ComboxPenColor);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        ComboxBrushColor = new ColorCombox(centralWidget);
        ComboxBrushColor->setObjectName(QStringLiteral("ComboxBrushColor"));
        sizePolicy1.setHeightForWidth(ComboxBrushColor->sizePolicy().hasHeightForWidth());
        ComboxBrushColor->setSizePolicy(sizePolicy1);
        ComboxBrushColor->setMinimumSize(QSize(105, 32));
        ComboxBrushColor->setMaximumSize(QSize(105, 32));
        ComboxBrushColor->setStyleSheet(QStringLiteral("border-image: url(:/EClassPic/EClassPic/brushcolor1.png);"));

        horizontalLayout->addWidget(ComboxBrushColor);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addLayout(verticalLayout);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setLayoutDirection(Qt::LeftToRight);
        mainToolBar->setMovable(false);
        mainToolBar->setAllowedAreas(Qt::NoToolBarArea);
        mainToolBar->setIconSize(QSize(120, 30));
        mainToolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);

        mainToolBar->addAction(actionEnterClass);
        mainToolBar->addAction(actionLeaveClass);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionClearScreen);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionExit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionEnterClass->setText(QApplication::translate("MainWindow", "EnterClass", 0));
        actionLeaveClass->setText(QApplication::translate("MainWindow", "LeaveClass", 0));
        actionClearScreen->setText(QApplication::translate("MainWindow", "ClearScreen", 0));
        actionExit->setText(QString());

        const bool __sortingEnabled = listWidget->isSortingEnabled();
        listWidget->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("MainWindow", "------Online-------", 0));
        QListWidgetItem *___qlistwidgetitem1 = listWidget->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("MainWindow", "Student1", 0));
        QListWidgetItem *___qlistwidgetitem2 = listWidget->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("MainWindow", "Student2", 0));
        QListWidgetItem *___qlistwidgetitem3 = listWidget->item(3);
        ___qlistwidgetitem3->setText(QApplication::translate("MainWindow", "Student3", 0));
        QListWidgetItem *___qlistwidgetitem4 = listWidget->item(4);
        ___qlistwidgetitem4->setText(QApplication::translate("MainWindow", "Student4", 0));
        QListWidgetItem *___qlistwidgetitem5 = listWidget->item(5);
        ___qlistwidgetitem5->setText(QApplication::translate("MainWindow", "Student5", 0));
        QListWidgetItem *___qlistwidgetitem6 = listWidget->item(6);
        ___qlistwidgetitem6->setText(QApplication::translate("MainWindow", "------Offline-------", 0));
        QListWidgetItem *___qlistwidgetitem7 = listWidget->item(7);
        ___qlistwidgetitem7->setText(QApplication::translate("MainWindow", "Student6", 0));
        listWidget->setSortingEnabled(__sortingEnabled);

        label->setText(QApplication::translate("MainWindow", "\346\210\221\347\232\204\347\224\273\346\235\277", 0));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "Scripts", 0));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "Line", 0));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "Rectangle", 0));
        comboBox->setItemText(3, QApplication::translate("MainWindow", "Ellipse", 0));

        comboBox->setCurrentText(QApplication::translate("MainWindow", "Scripts", 0));
        comboxPenWidth->setText(QString());
        ComboxPenColor->setText(QString());
        ComboxBrushColor->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
