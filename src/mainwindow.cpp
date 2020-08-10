#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    highlighter = new SyntaxHighlighter(ui->codeEdit->document());

    wManager = &WindowManager::getInstance();
    wManager->setUp(this,
                    ui->controlsWidget,
                    ui->vulkanWidget->getVulkanWindow()->getRenderer(),
                    ui->codeEdit,
                    ui->outputEdit);

}

MainWindow::~MainWindow()
{
    delete ui;
}

