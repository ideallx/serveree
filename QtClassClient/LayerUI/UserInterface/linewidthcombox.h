#ifndef LINEWIDTHCOMBOX_H
#define LINEWIDTHCOMBOX_H

#include <QResizeEvent>
#include <QToolButton>

class LineWidthCombox : public QToolButton
{
    Q_OBJECT

public:
    LineWidthCombox(QWidget *parent = 0);
    ~LineWidthCombox();

private:
    QMenu* createLineMenu();
    QIcon createLineIcon(int width);

signals:
    void signalWidthChanged(int width);

private slots:
    void onWidthChanged();
};

#endif // LINEWIDTHCOMBOX_H
