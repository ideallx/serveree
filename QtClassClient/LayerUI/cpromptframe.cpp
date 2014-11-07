#include "cpromptframe.h"
#include <QMessageBox>
#include "../UserInterface/prompt.h"

CPromptFrame::CPromptFrame()
{
}

void CPromptFrame::prompt(int result, QWidget *parent) {
    Prompt p(result, parent);
    p.exec();
}

void CPromptFrame::prompt(QString prompt, QWidget* parent) {
    Prompt p(prompt, parent);
    p.show();
}
