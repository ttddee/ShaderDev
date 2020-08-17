#include "mainwindow.h"

#include <QApplication>
#include <QVulkanWindow>

//#include "vulkan/vulkan.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Register custom meta types - Not sure if this is needed??!
    //qRegisterMetaType<ShaderCode>();
    //qRegisterMetaType<std::vector<unsigned int>>();

    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    auto title = QString("ShaderDev - v%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD);
    w.setWindowTitle(title);
    w.show();

    return a.exec();
}
