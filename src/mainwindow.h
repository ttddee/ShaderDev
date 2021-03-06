#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "syntaxhighlighter.h"
#include "windowmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    void setStatusMessage(const QString& text);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    SyntaxHighlighter *highlighter;
    WindowManager* wManager;

};
#endif // MAINWINDOW_H
