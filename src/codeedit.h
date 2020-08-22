#ifndef CODEEDIT_H
#define CODEEDIT_H

#include <QObject>
#include <QPlainTextEdit>

#include <SpvShaderCompiler.h>

#include "globals.h"

using namespace ShaderDev;

class CodeEdit : public QPlainTextEdit
{
    Q_OBJECT

public:
    CodeEdit(QWidget *parent = nullptr);
    void lineNumberAreaPaintEvent(QPaintEvent *event);
    int lineNumberAreaWidth();

    ShaderCode spirV;

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    SpvCompiler compiler;
    std::string code;
    QWidget *lineNumberArea;


signals:
    void requestErrorMessageUpdate(const std::string&);
    void shaderCompiledSuccessfully();

private slots:
    void handleCodeHasChanged();
    void updateLineNumberAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
};

#endif // CODEEDIT_H
