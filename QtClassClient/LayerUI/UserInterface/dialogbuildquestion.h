#ifndef DIALOGBUILDQUESTION_H
#define DIALOGBUILDQUESTION_H

#include <QDialog>

namespace Ui {
class DialogBuildQuestion;
}

class DialogBuildQuestion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBuildQuestion(QWidget *parent = 0);
    ~DialogBuildQuestion();

private slots:
    void on_tbChoiceA_clicked();

    void on_tbChoiceB_clicked();

    void on_tbChoiceC_clicked();

    void on_tbChoiceD_clicked();

    void on_tbBoolTrue_clicked();

    void on_tbBoolFalse_clicked();

    void on_pbAccount_clicked();

private:
    Ui::DialogBuildQuestion *ui;
};

#endif // DIALOGBUILDQUESTION_H
