#include "cpromptframe.h"
#include <QMessageBox>
#include "../UserInterface/prompt.h"
#include "dialogpixmap.h"

static Prompt* promDialog = NULL;


CPromptFrame::CPromptFrame()
{
}

QDialog* CPromptFrame::prompt(int result, QWidget *parent) {
    QDialog* d = new Prompt(result, parent);
#ifdef _TEST_PROMPT_POS_
    d->setGeometry(0, 0, d->geometry().width(), d->geometry().height());
#endif
    return d;
}

QDialog* CPromptFrame::prompt(QString prompt, QWidget* parent) {
    QDialog* d = new Prompt(prompt, parent);
#ifdef _TEST_PROMPT_POS_
    d->setGeometry(0, 0, d->geometry().width(), d->geometry().height());
#endif
    return d;
}

QDialog* CPromptFrame::racePrompt(QWidget* parent) {
    QDialog* d = new DialogPixmap(parent);
#ifdef _TEST_PROMPT_POS_
    d->setGeometry(0, 0, d->geometry().width(), d->geometry().height());
#endif
    return d;
}
