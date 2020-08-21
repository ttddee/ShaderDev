#ifndef LINENUMBERAREA_H
#define LINENUMBERAREA_H

#include <QObject>
#include <QWidget>

#include "codeedit.h"

class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    LineNumberArea(CodeEdit *editor);

    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);

private:
    CodeEdit *codeEditor;
};
#endif // LINENUMBERAREA_H
