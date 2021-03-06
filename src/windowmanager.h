#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>

#include "codeedit.h"
#include "controlswidget.h"
#include "vulkanwindow.h"
#include "outputedit.h"

class MainWindow;

class WindowManager : public QObject
{
    Q_OBJECT

public:
    WindowManager(MainWindow* w, ControlsWidget* c, VulkanWindow* v, CodeEdit* e, OutputEdit* oe);

private:
    MainWindow* mainWindow;
    ControlsWidget* controlsWidget;
    VulkanWindow* vulkanWindow;
    CodeEdit* codeEdit;
    OutputEdit* outputEdit;

public slots:
    void handleRendererHasBeenCreated();
    void handleImagePathHasChanged(const QString& path);
    void handleFileLoadingRequest(const QString& path);
    void handleShaderSavingRequest(const QString& path);
    void handleCompiledSavingRequest(const QString& path);
    void handleRequestErrorMessageUpdate(const std::string& msg);
    void handleShaderCompiled();
    void handleOriginalCheckboxStateChanged(bool state);

};

#endif // WINDOWMANAGER_H
