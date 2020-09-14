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
    connect(ui->saveShaderButton, &QPushButton::clicked,
            this, &ControlsWidget::handleSaveShaderButtonClicked);
    connect(ui->saveCompiledButton, &QPushButton::clicked,
            this, &ControlsWidget::handleSaveCompiledButtonClicked);
    connect(ui->originalCheckBox, &QCheckBox::stateChanged,
            this, &ControlsWidget::handleOriginalCheckboxStateChanged);
}

void ControlsWidget::handleShaderHasBeenSaved(const QString& path)
{
    fileIsDirty = false;
    ui->fileNameLabel->setText(fileName);
    QFileInfo fi(path);
    ui->fileNameLabel->setText(fi.fileName());
    fileName = fi.fileName();
    shaderPath = path;
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

        emit requestFileLoading(shaderPath);
    }
}

void ControlsWidget::handleSaveShaderButtonClicked()
{
    auto saveFileName = QFileDialog::getSaveFileName(this,
                                                     tr("Save Shader"), "",
                                                     tr("Shader (*.comp)"));
    if(!saveFileName.isEmpty())
    {
        emit requestShaderSaving(saveFileName);
    }
}

void ControlsWidget::handleSaveCompiledButtonClicked()
{
    auto saveFileName = QFileDialog::getSaveFileName(this,
                                                     tr("Save SPV"), "",
                                                     tr("SPIR-V (*.spv)"));
    if(!saveFileName.isEmpty())
    {
        emit requestCompiledSaving(saveFileName);
    }
}

void ControlsWidget::handleCodeHasChanged()
{
    fileIsDirty = true;
    if(fileName.size() > 0)
    {
        ui->fileNameLabel->setText(fileName + "*");
    }
}

void ControlsWidget::handleOriginalCheckboxStateChanged(int state)
{
    if(state == 0)
    {
        emit originalCheckboxStateChanged(false);
    }
    else
    {
        emit originalCheckboxStateChanged(true);
    }
}

ControlsWidget::~ControlsWidget()
{
    delete ui;
}
