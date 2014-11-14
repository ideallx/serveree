#ifndef WIDGETWARELISTITEM_H
#define WIDGETWARELISTITEM_H

#include <QWidget>

namespace Ui {
class WidgetWareListItem;
}

class WidgetWareListItem : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetWareListItem(QString filename, QWidget *parent = 0);
    ~WidgetWareListItem();

private slots:
    void on_tbRun_clicked();
    void on_tbRemove_clicked();

signals:
    void runFile(QString filename);
    void removeFile(QString filename);

private:
    Ui::WidgetWareListItem *ui;
    QString m_filename;
};

#endif // WIDGETWARELISTITEM_H
