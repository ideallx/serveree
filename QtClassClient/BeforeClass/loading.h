#ifndef _BEFORECLASS_LOADING_H_
#define _BEFORECLASS_LOADING_H_

#include <QObject>
#include "../Reliable/DataStructure/TSQueue.h"
#include "../Reliable/DataUnit/CMessage.h"

class Loading : public QObject{
    Q_OBJECT

public:
    Loading() : allMsgs(new TSQueue<ts_msg>()) {}
    virtual ~Loading() {}

    void sortByTime();

    void recv(ts_msg& msg);

signals:
    void progressChanged(int percentage);

private:
    TSQueue<ts_msg>* allMsgs;
};

#endif
