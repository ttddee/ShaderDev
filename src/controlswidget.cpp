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
    //dialog.setOption(QFileDialog::DontUseNativeDialog);
    if (dialog.exec())
    {
        auto files = dialog.selectedFiles();
        imagePath = files[0];
        emit imagePathHasChanged(imagePath);
    }

}

ControlsWidget::~ControlsWidget()
{
    delete ui;
}
