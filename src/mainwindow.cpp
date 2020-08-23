#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    highlighter = new SyntaxHighlighter(ui->codeEdit->document());

    wManager = new WindowManager(this,
                             ui->controlsWidget,
                             ui->vulkanWidget->getVulkanWindow(),
                             ui->codeEdit,
                             ui->outputEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete wManager;
}

