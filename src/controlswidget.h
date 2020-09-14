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

    void handleShaderHasBeenSaved(const QString& path);

private:
    Ui::ControlsWidget *ui;
    QString imagePath;
    QString shaderPath;
    QString fileName;
    bool fileIsDirty = false;

signals:
    void imagePathHasChanged(const QString& path);
    void requestFileLoading(const QString& path);
    void requestShaderSaving(const QString& path);
    void requestCompiledSaving(const QString& path);
    void originalCheckboxStateChanged(bool state);

public slots:
    void handleLoadImageButtonClicked();
    void handleLoadShaderButtonClicked();
    void handleSaveShaderButtonClicked();
    void handleSaveCompiledButtonClicked();
    void handleCodeHasChanged();
    void handleOriginalCheckboxStateChanged(int state);
};

#endif // CONTROLSWIDGET_H
