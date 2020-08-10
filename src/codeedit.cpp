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
    std::cout << "handleCodeHasChanged" << std::endl;
    code.clear();
    code.append(this->document()->toPlainText().toStdString());

    if (compiler.compileGLSLFromCode(code.data(), "comp"))
    {
        std::cout << "valid" << std::endl;
        spirV = compiler.getSpirV();
        //const uint32_t* c = compiler.getSpirV();
        emit shaderCompiledSuccessfully(spirV);
        std::cout << "Shader compiled successfully." << std::endl;
    }
    else
    {
        std::cout << "NOT valid" << std::endl;
        std::cout << compiler.getError() << std::endl;
    }
    emit requestErrorMessageUpdate(compiler.getError());
}
