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
    QVBoxLayout *verticalLayout_3;
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
    QGroupBox *gbTools;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_2;
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
        CourseWareWidget->resize(258, 651);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(CourseWareWidget->sizePolicy().hasHeightForWidth());
        CourseWareWidget->setSizePolicy(sizePolicy);
        CourseWareWidget->setStyleSheet(QLatin1String("QGroupBox#gbCourseware {\n"
"	background-color: rgb(18, 145, 113);\n"
"	border: none;\n"
"}\n"
"\n"
"QToolButton#tbUpload, #tbSync {	\n"
"	border-style: outset;\n"
"	border-width: 1px;\n"
"	border-color: white;\n"
"}\n"
"\n"
"QGroupBox#gbTools {\n"
"	background-color: rgb(106, 160, 127);\n"
"	border: none;\n"
"}"));
        verticalLayout_3 = new QVBoxLayout(CourseWareWidget);
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
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
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
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


        verticalLayout_3->addWidget(gbCourseware);

        gbTools = new QGroupBox(CourseWareWidget);
        gbTools->setObjectName(QStringLiteral("gbTools"));
        gbTools->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(gbTools);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        tbUpload = new QToolButton(gbTools);
        tbUpload->setObjectName(QStringLiteral("tbUpload"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tbUpload->sizePolicy().hasHeightForWidth());
        tbUpload->setSizePolicy(sizePolicy2);
        tbUpload->setMinimumSize(QSize(0, 40));
        tbUpload->setFont(font);
        tbUpload->setStyleSheet(QStringLiteral(""));
        tbUpload->setAutoRaise(true);

        horizontalLayout_2->addWidget(tbUpload);

        tbSync = new QToolButton(gbTools);
        tbSync->setObjectName(QStringLiteral("tbSync"));
        sizePolicy2.setHeightForWidth(tbSync->sizePolicy().hasHeightForWidth());
        tbSync->setSizePolicy(sizePolicy2);
        tbSync->setMinimumSize(QSize(0, 40));
        tbSync->setFont(font);
        tbSync->setStyleSheet(QStringLiteral(""));
        tbSync->setToolButtonStyle(Qt::ToolButtonTextOnly);
        tbSync->setAutoRaise(true);

        horizontalLayout_2->addWidget(tbSync);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        tbPrev = new QToolButton(gbTools);
        tbPrev->setObjectName(QStringLiteral("tbPrev"));
        sizePolicy2.setHeightForWidth(tbPrev->sizePolicy().hasHeightForWidth());
        tbPrev->setSizePolicy(sizePolicy2);
        tbPrev->setMaximumSize(QSize(16777215, 40));
        QIcon icon;
        icon.addFile(QStringLiteral(":/icon/ui/icon/l.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbPrev->setIcon(icon);
        tbPrev->setIconSize(QSize(40, 40));
        tbPrev->setAutoRaise(true);

        horizontalLayout->addWidget(tbPrev);

        tbStart = new QToolButton(gbTools);
        tbStart->setObjectName(QStringLiteral("tbStart"));
        sizePolicy2.setHeightForWidth(tbStart->sizePolicy().hasHeightForWidth());
        tbStart->setSizePolicy(sizePolicy2);
        tbStart->setMaximumSize(QSize(16777215, 40));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/icon/ui/icon/run.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbStart->setIcon(icon1);
        tbStart->setIconSize(QSize(40, 40));
        tbStart->setAutoRaise(true);

        horizontalLayout->addWidget(tbStart);

        tbNext = new QToolButton(gbTools);
        tbNext->setObjectName(QStringLiteral("tbNext"));
        sizePolicy2.setHeightForWidth(tbNext->sizePolicy().hasHeightForWidth());
        tbNext->setSizePolicy(sizePolicy2);
        tbNext->setMaximumSize(QSize(16777215, 40));
        tbNext->setStyleSheet(QStringLiteral(""));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/icon/ui/icon/r.png"), QSize(), QIcon::Normal, QIcon::Off);
        tbNext->setIcon(icon2);
        tbNext->setIconSize(QSize(40, 40));
        tbNext->setAutoRaise(true);

        horizontalLayout->addWidget(tbNext);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_3->addWidget(gbTools);


        retranslateUi(CourseWareWidget);

        QMetaObject::connectSlotsByName(CourseWareWidget);
    } // setupUi

    void retranslateUi(QWidget *CourseWareWidget)
    {
        CourseWareWidget->setWindowTitle(QApplication::translate("CourseWareWidget", "Form", 0));
        gbCourseware->setTitle(QString());
        label->setText(QApplication::translate("CourseWareWidget", "\346\225\231\345\270\210\350\257\276\344\273\266( ", 0));
        lbWareCount->setText(QApplication::translate("CourseWareWidget", "0", 0));
        label_3->setText(QApplication::translate("CourseWareWidget", "\357\274\211", 0));
        tbExitWare->setText(QApplication::translate("CourseWareWidget", "    X    ", 0));
        gbTools->setTitle(QString());
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
