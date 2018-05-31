#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void OnOpenClick();
    void OnNewClick();
    void OnSaveClick();
    void OnFindComponentsClick();

private:
    void CreateGraphSubWindow(const QString& title, const QString& text);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
