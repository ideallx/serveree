#include "cpromptframe.h"

CPromptFrame::CPromptFrame()
{
}

void CPromptFrame::prompt(int result, QWidget *parent) {
    QMessageBox::warning(parent, QObject::tr("interactive class"), AllPrompts[result]);
}
