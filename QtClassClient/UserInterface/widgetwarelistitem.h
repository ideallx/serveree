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
    explicit WidgetWareListItem(QByteArray filename, QWidget *parent = 0);
    ~WidgetWareListItem();

private slots:
    void on_tbRun_clicked();
    void on_tbRemove_clicked();

signals:
    void runFile(QByteArray filename);
    void removeFile(QByteArray filename);

private:
    Ui::WidgetWareListItem *ui;
    QByteArray m_filename;
};

#endif // WIDGETWARELISTITEM_H
