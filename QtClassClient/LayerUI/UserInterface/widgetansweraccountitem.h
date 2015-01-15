#ifndef WIDGETANSWERACCOUNTITEM_H
#define WIDGETANSWERACCOUNTITEM_H

#include <QWidget>

namespace Ui {
class WidgetAnswerAccountItem;
}

class WidgetAnswerAccountItem : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetAnswerAccountItem(QWidget *parent = 0);
    ~WidgetAnswerAccountItem();

    void setValue(int correct, int wrong, int blank);

private:
    Ui::WidgetAnswerAccountItem *ui;
};

#endif // WIDGETANSWERACCOUNTITEM_H
