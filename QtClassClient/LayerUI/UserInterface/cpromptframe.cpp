#include "cpromptframe.h"
#include <QMessageBox>
#include "../UserInterface/prompt.h"

static Prompt* promDialog = NULL;

CPromptFrame::CPromptFrame()
{
}

void CPromptFrame::prompt(int result, QWidget *parent) {
    if (NULL == promDialog) {
        Prompt *p = new Prompt(result, parent);
        promDialog = p;
        p->exec();
    } else {
        promDialog->setPrompt(result);
        promDialog->setHidden(false);
    }
}

void CPromptFrame::prompt(QString prompt, QWidget* parent) {
    if (NULL == promDialog) {
        Prompt *p = new Prompt(prompt, parent);
        promDialog = p;
        p->exec();
    } else {
        promDialog->setPrompt(prompt);
        promDialog->setHidden(false);
    }
}
