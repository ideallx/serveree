#include "cpromptframe.h"
#include <QMessageBox>
#include "dialogpixmap.h"

static QDialog* preDialog = NULL;

CPromptFrame::CPromptFrame()
{
}

QDialog* CPromptFrame::prompt(int result, WORD pc, QWidget *parent) {
    if (preDialog) {
        delete preDialog;
    }
    QDialog* d = new Prompt(result, pc, parent);
    preDialog = d;
#ifdef _TEST_PROMPT_POS_
    d->setGeometry(0, 0, d->geometry().width(), d->geometry().height());
#endif
    return d;
}

QDialog* CPromptFrame::prompt(QString prompt, WORD pc, QWidget* parent) {
    if (preDialog) {
        delete preDialog;
    }
    QDialog* d = new Prompt(prompt, pc, parent);
    preDialog = d;
#ifdef _TEST_PROMPT_POS_
    d->setGeometry(0, 0, d->geometry().width(), d->geometry().height());
#endif
    return d;
}

QDialog* CPromptFrame::racePrompt(QWidget* parent) {
    if (preDialog) {
        delete preDialog;
    }
    QDialog* d = new DialogPixmap(parent);
    preDialog = d;
#ifdef _TEST_PROMPT_POS_
    d->setGeometry(0, 0, d->geometry().width(), d->geometry().height());
#endif
    return d;
}
