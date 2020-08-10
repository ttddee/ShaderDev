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

signals:
    void imagePathHasChanged(const QString& path);

public slots:
    void handleLoadImageButtonClicked();
};

#endif // CONTROLSWIDGET_H
