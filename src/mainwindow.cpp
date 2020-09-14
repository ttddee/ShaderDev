#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStatusBar>

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

void MainWindow::setStatusMessage(const QString &text)
{
    statusBar()->showMessage(text);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete wManager;
}

