#include "windowmanager.h"

#include <iostream>
#include <fstream>

#include <QMessageBox>

#include "mainwindow.h"
#include "vulkanrenderer.h"

WindowManager::WindowManager(MainWindow* w, ControlsWidget* c, VulkanWindow* v, CodeEdit* e, OutputEdit* oe)
{
    mainWindow = w;
    controlsWidget = c;
    vulkanWindow = v;
    codeEdit = e;
    outputEdit = oe;

    connect(vulkanWindow, &VulkanWindow::rendererHasBeenCreated,
            this, &WindowManager::handleRendererHasBeenCreated);
    connect(controlsWidget, &ControlsWidget::imagePathHasChanged,
            this, &WindowManager::handleImagePathHasChanged);
    connect(controlsWidget, &ControlsWidget::requestFileLoading,
            this, &WindowManager::handleFileLoadingRequest);
    connect(controlsWidget, &ControlsWidget::requestShaderSaving,
            this, &WindowManager::handleShaderSavingRequest);
    connect(controlsWidget, &ControlsWidget::requestCompiledSaving,
            this, &WindowManager::handleCompiledSavingRequest);
    connect(codeEdit, &CodeEdit::requestErrorMessageUpdate,
            this, &WindowManager::handleRequestErrorMessageUpdate);
    connect(codeEdit, &CodeEdit::shaderCompiledSuccessfully,
            this, &WindowManager::handleShaderCompiled);
    connect(codeEdit, &CodeEdit::textChanged,
            controlsWidget, &ControlsWidget::handleCodeHasChanged);
    connect(controlsWidget, &ControlsWidget::originalCheckboxStateChanged,
            this, &WindowManager::handleOriginalCheckboxStateChanged);
}

void WindowManager::handleRendererHasBeenCreated()
{
    QString status = "GPU: " + vulkanWindow->getRenderer()->getGpuName();
    mainWindow->setStatusMessage(status);
}

void WindowManager::handleImagePathHasChanged(const QString& path)
{
    vulkanWindow->getRenderer()->updateImage(path);
}

void WindowManager::handleFileLoadingRequest(const QString& path)
{
    QFile f(path);
    if (!f.open((QFile::ReadOnly | QFile::Text)))
    {
        qWarning("Failed to open file.");
    }

    QTextStream in (&f);
    auto t = in.readAll();

    codeEdit->blockSignals(true);
    codeEdit->setPlainText(t);
    codeEdit->update();
    codeEdit->blockSignals(false);
}

void WindowManager::handleShaderSavingRequest(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::information(controlsWidget, tr("Unable to open file"),
        file.errorString());
        return;
    }
    QTextStream out(&file);
    out << codeEdit->document()->toPlainText();
    controlsWidget->handleShaderHasBeenSaved(path);
}

void WindowManager::handleCompiledSavingRequest(const QString& path)
{
    if (codeEdit->spirV.size() == 0)
    {
        QMessageBox::information(controlsWidget, "Unable to open file", "Nothing compiled yet?");
    }
    else
    {
        auto data = vulkanWindow->getRenderer()->uintVecToCharVec(codeEdit->spirV);

        std::ofstream f;
        f.open(path.toStdString(), std::ios_base::binary);
        f.write((char*) &data[0], data.size() * sizeof (char));
        f.close();
    }
}

void WindowManager::handleRequestErrorMessageUpdate(const std::string& msg)
{
    outputEdit->setErrorMsg(msg);
}

void WindowManager::handleShaderCompiled()
{
    vulkanWindow->getRenderer()->updateShader(codeEdit->spirV);
}

void WindowManager::handleOriginalCheckboxStateChanged(bool state)
{
    vulkanWindow->setShowOriginal(state);
    vulkanWindow->getRenderer()->updateShader(codeEdit->spirV);
}
