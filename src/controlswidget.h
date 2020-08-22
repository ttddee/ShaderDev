#ifndef CONTROLSWIDGET_H
#define CONTROLSWIDGET_H

#include <QWidget>

namespace Ui {
class ControlsWidget;
}

class ControlsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlsWidget(QWidget *parent = nullptr);
    ~ControlsWidget();

    void setGpuLabel(const QString& s);

private:
    Ui::ControlsWidget *ui;
    QString imagePath;
    QString shaderPath;
    bool fileIsDirty = false;
    QString fileName;

signals:
    void imagePathHasChanged(const QString& path);
    void shaderWasLoaded(const QString& path);

public slots:
    void handleLoadImageButtonClicked();
    void handleLoadShaderButtonClicked();
    void handleCodeHasChanged();
};

#endif // CONTROLSWIDGET_H
