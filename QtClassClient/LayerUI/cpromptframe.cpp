#include "cpromptframe.h"
#include <QMessageBox>
#include "../UserInterface/prompt.h"

CPromptFrame::CPromptFrame()
{
}

void CPromptFrame::prompt(int result, QWidget *parent) {
    Prompt p(result, parent);
    p.setModal(true);
    p.exec();
}
