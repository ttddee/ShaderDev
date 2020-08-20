#include "mainwindow.h"

#include <QApplication>
#include <QVulkanWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load style sheet
    QFile f(":/style/stylesheet.qss");
    f.open(QFile::ReadOnly);
    QString style = QLatin1String(f.readAll());
    a.setStyleSheet(style);

    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    auto title = QString("ShaderDev - v%1.%2.%3").arg(VERSION_MAJOR).arg(VERSION_MINOR).arg(VERSION_BUILD);
    w.setWindowTitle(title);

    w.show();

    return a.exec();
}
