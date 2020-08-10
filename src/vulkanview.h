#ifndef VULKANVIEW_H
#define VULKANVIEW_H

#include <QWidget>

#include "vulkanwindow.h"

class VulkanView : public QWidget
{
    Q_OBJECT
public:
    explicit VulkanView(QWidget *parent = nullptr);
    VulkanWindow* getVulkanWindow();

private:
    QWidget* vulkanWrapper;
    VulkanWindow* vulkanWindow;
    QVulkanInstance instance;

signals:

};

#endif // VULKANVIEW_H
