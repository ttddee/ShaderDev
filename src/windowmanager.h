#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <QObject>

#include "codeedit.h"
#include "controlswidget.h"
#include "vulkanrenderer.h"
#include "outputedit.h"

class MainWindow;

class WindowManager : public QObject
{
    Q_OBJECT

public:
    static WindowManager& getInstance();
    WindowManager(WindowManager const&) = delete;
    void operator=(WindowManager const&) = delete;

    void setUp(MainWindow* w, ControlsWidget* c, VulkanRenderer* r, CodeEdit* e, OutputEdit* oe);

    void setGpuLabel(const QString& s);

private:
    WindowManager() {}

    MainWindow* mainWindow;
    ControlsWidget* controlsWidget;
    VulkanRenderer* vulkanRenderer;
    CodeEdit* codeEdit;
    OutputEdit* outputEdit;

public slots:
    void handleImagePathHasChanged(const QString& path);
    void handleRequestErrorMessageUpdate(const std::string& msg);
    void handleShaderCompiled(const std::vector<unsigned int>&);

};

#endif // WINDOWMANAGER_H
