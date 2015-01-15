#ifndef DIALOGCHOOSESHAPE_H
#define DIALOGCHOOSESHAPE_H

#include <QDialog>

namespace Ui {
class DialogChooseShape;
}

class DialogChooseShape : public QDialog
{
    Q_OBJECT

public:
    explicit DialogChooseShape(QWidget *parent = 0);
    ~DialogChooseShape();

private:
    Ui::DialogChooseShape *ui;
};

#endif // DIALOGCHOOSESHAPE_H
