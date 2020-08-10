#ifndef CODEEDIT_H
#define CODEEDIT_H

#include <QObject>
#include <QTextEdit>

#include <SpvShaderCompiler.h>

class CodeEdit : public QTextEdit
{
    Q_OBJECT

public:
    CodeEdit(QWidget *parent = nullptr);

private:
    SpvCompiler compiler;
    std::string code;
    std::vector<unsigned int> spirV;

signals:
    void requestErrorMessageUpdate(const std::string&);
    void shaderCompiledSuccessfully(const std::vector<unsigned int>&);

private slots:
    void handleCodeHasChanged();
};

#endif // CODEEDIT_H
