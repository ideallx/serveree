/********************************************************************************
** Form generated from reading UI file 'coursewarewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COURSEWAREWIDGET_H
#define UI_COURSEWAREWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CourseWareWidget
{
public:
    QHBoxLayout *horizontalLayout_2;
    QGroupBox *gbCourseware;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    QLabel *lbWareCount;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QToolButton *tbExitWare;
    QListWidget *lsWare;
    QGroupBox *gbWareCtrl;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *tbUpload;
    QToolButton *tbSync;
    QHBoxLayout *horizontalLayout;
    QToolButton *tbPrev;
    QToolButton *tbStart;
    QToolButton *tbNext;

    void setupUi(QWidget *CourseWareWidget)
    {
        if (CourseWareWidget->objectName().isEmpty())
            CourseWareWidget->setObjectName(QStringLiteral("CourseWareWidget"));
        CourseWareWidget->resize(301, 651);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CourseWareWidget->sizePolicy().hasHeightForWidth());
        CourseWareWidget->setSizePolicy(sizePolicy);
        CourseWareWidget->setStyleSheet(QLatin1String("QToolButton#tbUpload, #tbSync {	\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-color: black;\n"
"}"));
        horizontalLayout_2 = new QHBoxLayout(CourseWareWidget);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        gbCourseware = new QGroupBox(CourseWareWidget);
        gbCourseware->setObjectName(QStringLiteral("gbCourseware"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gbCourseware->sizePolicy().hasHeightForWidth());
        gbCourseware->setSizePolicy(sizePolicy1);
        gbCourseware->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(gbCourseware);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(0);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        label = new QLabel(gbCourseware);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(0, 35));
        QFont font;
        font.setPointSize(12);
        label->setFont(font);

        horizontalLayout_5->addWidget(label);

        lbWareCount = new QLabel(gbCourseware);
        lbWareCount->setObjectName(QStringLiteral("lbWareCount"));
        lbWareCount->setMinimumSize(QSize(0, 35));
        lbWareCount->setFont(font);

        horizontalLayout_5->addWidget(lbWareCount);

        label_3 = new QLabel(gbCourseware);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMinimumSize(QSize(0, 35));
        label_3->setFont(font);

        horizontalLayout_5->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        tbExitWare = new QToolButton(gbCourseware);
        tbExitWare->setObjectName(QStringLiteral("tbExitWare"));
        QFont font1;
        font1.setFamily(QStringLiteral("Aharoni"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setWeight(75);
        tbExitWare->setFont(font1);
        tbExitWare->setStyleSheet(QStringLiteral(""));
        tbExitWare->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        tbExitWare->setAutoRaise(true);
        tbExitWare->setArrowType(Qt::NoArrow);

        horizontalLayout_5->addWidget(tbExitWare);


        verticalLayout->addLayout(horizontalLayout_5);

        lsWare = new QListWidget(gbCourseware);
        lsWare->setObjectName(QStringLiteral("lsWare"));
        QFont font2;
        font2.setPointSize(9);
        lsWare->setFont(font2);

        verticalLayout->addWidget(lsWare);

        gbWareCtrl = new QGroupBox(gbCourseware);
        gbWareCtrl->setObjectName(QStringLiteral("gbWareCtrl"));
        gbWareCtrl->setStyleSheet(QStringLiteral("background-color: rgb(174, 175, 180);"));
        horizontalLayout_3 = new QHBoxLayout(gbWareCtrl);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        tbUpload = new QToolButton(gbWareCtrl);
        tbUpload->setObjectName(QStringLiteral("tbUpload"));
        tbUpload->setMinimumSize(QSize(0, 30));
        tbUpload->setFont(font);
        tbUpload->setStyleSheet(QStringLiteral(""));
        tbUpload->setAutoRaise(true);

        horizontalLayout_3->addWidget(tbUpload);

        tbSync = new QToolButton(gbWareCtrl);
        tbSync->setObjectName(QStringLiteral("tbSync"));
        tbSync->setMinimumSize(QSize(0, 30));
        tbSync->setFont(font);
        tbSync->setStyleSheet(QStringLiteral(""));
        tbSync->setToolButtonStyle(Qt::ToolButtonTextOnly);
        tbSync->setAutoRaise(true);

        horizontalLayout_3->addWidget(tbSync);


        verticalLayout->addWidget(gbWareCtrl);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tbPrev = new QToolButton(gbCourseware);
        tbPrev->setObjectName(QStringLiteral("tbPrev"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/ui/icon/prev.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPrev->setIcon(icon);
        tbPrev->setIconSize(QSize(40, 40));
        tbPrev->setAutoRaise(true);

        horizontalLayout->addWidget(tbPrev);

        tbStart = new QToolButton(gbCourseware);
        tbStart->setObjectName(QStringLiteral("tbStart"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/ui/icon/start.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbStart->setIcon(icon1);
        tbStart->setIconSize(QSize(40, 40));
        tbStart->setAutoRaise(true);

        horizontalLayout->addWidget(tbStart);

        tbNext = new QToolButton(gbCourseware);
        tbNext->setObjectName(QStringLiteral("tbNext"));
        tbNext->setStyleSheet(QStringLiteral(""));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/ui/icon/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbNext->setIcon(icon2);
        tbNext->setIconSize(QSize(40, 40));
        tbNext->setAutoRaise(true);

        horizontalLayout->addWidget(tbNext);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_2->addWidget(gbCourseware);


        retranslateUi(CourseWareWidget);

        QMetaObject::connectSlotsByName(CourseWareWidget);
    } // setupUi

    void retranslateUi(QWidget *CourseWareWidget)
    {
        CourseWareWidget->setWindowTitle(QApplication::translate("CourseWareWidget", "Form", 0));
        gbCourseware->setTitle(QString());
        label->setText(QApplication::translate("CourseWareWidget", "\346\225\231\345\270\210\350\257\276\344\273\266(", 0));
        lbWareCount->setText(QApplication::translate("CourseWareWidget", "0", 0));
        label_3->setText(QApplication::translate("CourseWareWidget", "\357\274\211", 0));
        tbExitWare->setText(QApplication::translate("CourseWareWidget", "    X    ", 0));
        gbWareCtrl->setTitle(QString());
        tbUpload->setText(QApplication::translate("CourseWareWidget", "\344\270\212\344\274\240\350\257\276\344\273\266", 0));
        tbSync->setText(QApplication::translate("CourseWareWidget", "\345\220\214\346\255\245\350\257\276\344\273\266", 0));
        tbPrev->setText(QApplication::translate("CourseWareWidget", "...", 0));
        tbStart->setText(QApplication::translate("CourseWareWidget", "...", 0));
        tbNext->setText(QApplication::translate("CourseWareWidget", "...", 0));
    } // retranslateUi

};

namespace Ui {
    class CourseWareWidget: public Ui_CourseWareWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COURSEWAREWIDGET_H
