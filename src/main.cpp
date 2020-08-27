#include "mainwindow.h"

#include <iostream>

#include <QApplication>
#include <QVulkanWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Load font
    int fontId = QFontDatabase::addApplicationFont(":/OpenSans-Regular.ttf");
    QFontDatabase::addApplicationFont(":/OpenSans-Bold.ttf");
    if (fontId != -1)
        a.setFont(QFont("Open Sans"));
    else
        std::cout << "Problem loading font." << std::endl;

    // Load style sheet
    QFile f(":/stylesheet.qss");
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
