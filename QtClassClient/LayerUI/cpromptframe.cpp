#include "cpromptframe.h"
#include <QMessageBox>
#include "../prompt.h"

CPromptFrame::CPromptFrame()
{
}

void CPromptFrame::prompt(int result, QWidget *parent) {
    Prompt* p = new Prompt(parent);
    p->show();
}
