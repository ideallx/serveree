#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QAxWidget>
#include <QObject>>

class MyActiveX : public QAxWidget
{
    Q_OBJECT
    Q_CLASSINFO("Version", "2.0")
    Q_CLASSINFO("ClassID", "{7a4cffd8-cbcd-4ae9-ae7e-343e1e5710df}")
    Q_CLASSINFO("InterfaceID", "{6fb035bf-8019-48d8-be51-ef05427d8994}")
    Q_CLASSINFO("EventsID", "{c42fffdf-6557-47c9-817a-2da2228bc29c}")
    Q_CLASSINFO("Insertable", "yes")
    Q_CLASSINFO("ToSuperClass", "MyActiveX")

public:
    MyActiveX(QWidget *parent = 0) :
        QAxWidget(parent) {}

};

#endif // MYWIDGET_H
