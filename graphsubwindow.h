#ifndef GRAPHSUBWINDOW_H
#define GRAPHSUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
#include <QGraphicsScene>
#include <graphmanager.h>

namespace Ui {
class GraphSubWindow;
}

class GraphSubWindow : public QMdiSubWindow
{
    Q_OBJECT

public:
    explicit GraphSubWindow(QWidget *parent = 0);
    GraphSubWindow(QWidget *parent, const QString& inputText);
    ~GraphSubWindow();

    std::map<QString, QString>  Proceed();
    QString Save();
private:
    void DrawGraph();

    Ui::GraphSubWindow *ui;
    QGraphicsScene * graphicsScene;
    GraphManager *graphManager;
};

#endif // GRAPHSUBWINDOW_H
