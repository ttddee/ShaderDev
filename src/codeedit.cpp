#include "codeedit.h"

#include <iostream>

CodeEdit::CodeEdit(QWidget *parent)
    : QTextEdit(parent)
{
    connect(this, &CodeEdit::textChanged,
            this, &CodeEdit::handleCodeHasChanged);
}

void CodeEdit::handleCodeHasChanged()
{
    code.clear();
    code.append(this->document()->toPlainText().toStdString());

    if (compiler.compileGLSLFromCode(code.data(), "comp"))
    {
        spirV = compiler.getSpirV();

        emit shaderCompiledSuccessfully();
    }
    else
    {
        std::cout << "Shader is not valid: " << std::endl;
        std::cout << compiler.getError() << std::endl;

    }
    emit requestErrorMessageUpdate(compiler.getError());
}
