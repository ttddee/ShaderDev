#include "controlswidget.h"
#include "ui_controlswidget.h"

#include <QFileDialog>

ControlsWidget::ControlsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlsWidget)
{
    ui->setupUi(this);

    connect(ui->loadImageButton, &QPushButton::clicked,
            this, &ControlsWidget::handleLoadImageButtonClicked);
    connect(ui->loadShaderButton, &QPushButton::clicked,
            this, &ControlsWidget::handleLoadShaderButtonClicked);
}

void ControlsWidget::setGpuLabel(const QString &s)
{
    ui->gpuLabel->setText(s);
}

void ControlsWidget::handleLoadImageButtonClicked()
{
    QFileDialog dialog(nullptr);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Images (*.jpg *.png)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDirectory(QCoreApplication::applicationDirPath());
    if (dialog.exec())
    {
        auto files = dialog.selectedFiles();
        imagePath = files[0];

        emit imagePathHasChanged(imagePath);
    }
}

void ControlsWidget::handleLoadShaderButtonClicked()
{
    QFileDialog dialog(nullptr);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setNameFilter(tr("Shaders (*.comp)"));
    dialog.setViewMode(QFileDialog::Detail);
    dialog.setDirectory(QCoreApplication::applicationDirPath());
    if (dialog.exec())
    {
        auto files = dialog.selectedFiles();
        shaderPath = files[0];

        QFileInfo fi(shaderPath);
        ui->fileNameLabel->setText(fi.fileName());
        fileName = fi.fileName();

        emit shaderWasLoaded(shaderPath);
    }
}

void ControlsWidget::handleCodeHasChanged()
{
    fileIsDirty = true;
    ui->fileNameLabel->setText(fileName + "*");
}

ControlsWidget::~ControlsWidget()
{
    delete ui;
}
