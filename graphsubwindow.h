#ifndef GRAPHSUBWINDOW_H
#define GRAPHSUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>

namespace Ui {
class GraphSubWindow;
}

class GraphSubWindow : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit GraphSubWindow(QWidget *parent = 0);
    GraphSubWindow(QWidget *parent, QString& inputText);
    ~GraphSubWindow();

private slots:
    void Proceed();
    void Save();
private:
    Ui::GraphSubWindow *ui;


};

#endif // GRAPHSUBWINDOW_H
