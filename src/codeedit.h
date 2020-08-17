#ifndef CODEEDIT_H
#define CODEEDIT_H

#include <QObject>
#include <QTextEdit>

#include <SpvShaderCompiler.h>

#include "globals.h"

using namespace ShaderDev;

class CodeEdit : public QTextEdit
{
    Q_OBJECT

public:
    CodeEdit(QWidget *parent = nullptr);
    ShaderCode spirV;

private:
    SpvCompiler compiler;
    std::string code;

signals:
    void requestErrorMessageUpdate(const std::string&);
    void shaderCompiledSuccessfully();

private slots:
    void handleCodeHasChanged();
};

#endif // CODEEDIT_H
