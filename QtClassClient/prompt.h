#ifndef PROMPT_H
#define PROMPT_H

#include <QDialog>

namespace Ui {
class Prompt;
}

class Prompt : public QDialog
{
    Q_OBJECT

public:
    explicit Prompt(QWidget *parent = 0);
    ~Prompt();

private:
    Ui::Prompt *ui;
};

#endif // PROMPT_H
