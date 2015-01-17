#ifndef DIALOGPIXMAP_H
#define DIALOGPIXMAP_H

#include <QDialog>

namespace Ui {
class DialogPixmap;
}

class DialogPixmap : public QDialog
{
    Q_OBJECT

public:
    explicit DialogPixmap(QWidget *parent = 0);
    ~DialogPixmap();

private slots:
    void on_toolButton_clicked();

private:
    Ui::DialogPixmap *ui;
};

#endif // DIALOGPIXMAP_H
