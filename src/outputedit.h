#ifndef OUTPUTEDIT_H
#define OUTPUTEDIT_H

#include <QObject>
#include <QTextEdit>

class OutputEdit : public QTextEdit
{
public:
    OutputEdit(QWidget *parent = nullptr);

    void setErrorMsg(const std::string& msg);
};

#endif // OUTPUTEDIT_H
