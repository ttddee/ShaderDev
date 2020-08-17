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
    //static WindowManager& getInstance();
    //WindowManager(WindowManager const&) = delete;
    //void operator=(WindowManager const&) = delete;

    //void setUp(MainWindow* w, ControlsWidget* c, VulkanRenderer* r, CodeEdit* e, OutputEdit* oe);

    void setGpuLabel(const QString& s);

private:
    //WindowManager() {}

    //WindowManager(WindowManager const&);

    MainWindow* mainWindow;
    ControlsWidget* controlsWidget;
    VulkanWindow* vulkanWindow;
    CodeEdit* codeEdit;
    OutputEdit* outputEdit;

    //std::shared_ptr<ShaderCode> code;

public slots:
    //void handleRendererHasInitialized(VulkanRenderer* r);
    void handleImagePathHasChanged(const QString& path);
    void handleRequestErrorMessageUpdate(const std::string& msg);
    void handleShaderCompiled();

};

#endif // WINDOWMANAGER_H
