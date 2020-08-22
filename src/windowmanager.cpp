#include "windowmanager.h"

#include <iostream>

#include "mainwindow.h"
#include "vulkanrenderer.h"

WindowManager::WindowManager(MainWindow* w, ControlsWidget* c, VulkanWindow* v, CodeEdit* e, OutputEdit* oe)
{
    mainWindow = w;
    controlsWidget = c;
    vulkanWindow = v;
    codeEdit = e;
    outputEdit = oe;

    qDebug("Initializing WindowManager");

    connect(vulkanWindow, &VulkanWindow::rendererHasBeenCreated,
            this, &WindowManager::handleRendererHasBeenCreated);
    connect(controlsWidget, &ControlsWidget::imagePathHasChanged,
            this, &WindowManager::handleImagePathHasChanged);
    connect(controlsWidget, &ControlsWidget::shaderWasLoaded,
            this, &WindowManager::handleShaderWasLoaded);
    connect(codeEdit, &CodeEdit::requestErrorMessageUpdate,
            this, &WindowManager::handleRequestErrorMessageUpdate);
    connect(codeEdit, &CodeEdit::shaderCompiledSuccessfully,
            this, &WindowManager::handleShaderCompiled);
    connect(codeEdit, &CodeEdit::textChanged,
            controlsWidget, &ControlsWidget::handleCodeHasChanged);
}

void WindowManager::handleRendererHasBeenCreated()
{
    controlsWidget->setGpuLabel(vulkanWindow->getRenderer()->getGpuName());
}

void WindowManager::handleImagePathHasChanged(const QString& path)
{
    vulkanWindow->getRenderer()->updateImage(path);
}

void WindowManager::handleShaderWasLoaded(const QString& path)
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

void WindowManager::handleRequestErrorMessageUpdate(const std::string& msg)
{
    outputEdit->setErrorMsg(msg);
}

void WindowManager::handleShaderCompiled()
{
    vulkanWindow->getRenderer()->updateShader(codeEdit->spirV);
}
