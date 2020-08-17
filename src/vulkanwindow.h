#ifndef VULKANWINDOW_H
#define VULKANWINDOW_H

#include <QObject>
#include <QVulkanWindow>
#include <QWindow>

class VulkanRenderer;

class VulkanWindow : public QVulkanWindow
{
public:
    QVulkanWindowRenderer *createRenderer() override;

    VulkanRenderer* getRenderer();

    //void acceptRendererHasInitialized();

private:
    void mousePressEvent(QMouseEvent *) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void mouseMoveEvent(QMouseEvent *) override;
    void wheelEvent(QWheelEvent *) override;

    VulkanRenderer* renderer;
    bool pressed = false;
    QPoint lastPos;
    float scale = 1.0f;

//signals:
//    void rendererHasInitialized(VulkanRenderer*);
};

#endif // VULKANWINDOW_H
