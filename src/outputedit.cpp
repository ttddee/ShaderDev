#include "outputedit.h"

#include <iostream>

OutputEdit::OutputEdit(QWidget *parent)
    : QTextEdit(parent)
{
    this->setReadOnly(true);
}

void OutputEdit::setErrorMsg(const std::string &msg)
{
    this->setText(QString::fromStdString(msg));
}
