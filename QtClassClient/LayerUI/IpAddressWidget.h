#ifndef IPADDRESSWIDGET_H
#define IPADDRESSWIDGET_H


#include <QtGui>
#include<QWidget>
#include<QSpinBox>
#include<QLabel>
#include<QPushButton>

#include<QVBoxLayout>
#include<QHBoxLayout>
#include<QMessageBox>

//IP地址输入框
class IpAddressWidget : public QWidget
{
    Q_OBJECT
private:
    QSpinBox *m_SpinBox[4];
    QLabel *m_Label[3];
    QString m_Separator;        //四个数字之间的分隔符
protected:
    bool eventFilter(QObject *object, QEvent *event);
public:
    IpAddressWidget(QWidget *parent = 0);
    ~IpAddressWidget();
    QString GetIpAddressString();
    void SetSeparator(const QString &separator);
};

//测试例子
class TestWidget : public QWidget
{
    Q_OBJECT
private:
    IpAddressWidget *ipAddressWidget;
    QPushButton *OKButton;

public:
    TestWidget(QWidget *parent = 0);
    ~TestWidget();

public slots:
    // void ClickedOKButton();
};


#endif // IPADDRESSWIDGET_H
