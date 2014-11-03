#ifndef WARELISTITEM_H
#define WARELISTITEM_H

#include <QListWidgetItem>

class WareListItem : public QListWidgetItem {
public:
    WareListItem();

    void mouseMoveEvent();
};

#endif // WARELISTITEM_H
