#ifndef GRAPHSUBWINDOW_H
#define GRAPHSUBWINDOW_H

#include <QWidget>
#include <QMdiSubWindow>
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
    Ui::GraphSubWindow *ui;

    GraphManager *graphManager;
};

#endif // GRAPHSUBWINDOW_H
