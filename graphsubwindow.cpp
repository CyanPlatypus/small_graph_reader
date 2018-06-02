#include "graphsubwindow.h"
#include "ui_graphsubwindow.h"
#include "graphmanager.h"

#include <QMdiSubWindow>
#include <QtCore>
#include <QtWidgets>
#include <queue>

using namespace std;

GraphSubWindow::GraphSubWindow(QWidget *parent) :
    QMdiSubWindow(parent),
    ui(new Ui::GraphSubWindow)
{
    ui->setupUi(this);
    setWidget(ui->widget);
}

GraphSubWindow::GraphSubWindow(QWidget *parent, const QString& inputText) :
    QMdiSubWindow(parent),
    ui(new Ui::GraphSubWindow),
    graphManager(new GraphManager(inputText))
{
    ui->setupUi(this);
    setWidget(ui->widget);
    ui->inputTextEdit->setPlainText(inputText);

    graphicsScene = new QGraphicsScene(this);

    ui->graphicsView->setScene(graphicsScene);

    DrawGraph();
}

GraphSubWindow::~GraphSubWindow()
{
    delete ui;
}

map<QString, QString> GraphSubWindow::Proceed(){
    return graphManager->FindConnectedComponents();

}


QString GraphSubWindow::Save(){
    return graphManager->Export();

}

void GraphSubWindow::DrawGraph(){

    QPen pen(Qt::black);

    std::map<QString, std::set<QString>> map = graphManager->GetInnerRepresentation();

    std::map<QString, QPair<qreal, qreal>> coords;

    for(auto& pair: map){
        qreal x = QRandomGenerator::global()->bounded(2, 300);
        qreal y = QRandomGenerator::global()->bounded(2, 300);
        coords[pair.first] = QPair<qreal, qreal>(x, y);
    }

    std::set<QString> visitedVertexes;
    std::queue<QString> vertexQueue;

    for(auto& pair: map){

        vertexQueue.push(pair.first);

        while (!vertexQueue.empty()) {
            QString vertex = vertexQueue.front();
            vertexQueue.pop();
            visitedVertexes.insert(vertex);

            //adjacent vertexes
            if(map.find(vertex)!= map.end()){
                for(auto& mateVertex : map[vertex]){
                    if(std::find(visitedVertexes.begin(), visitedVertexes.end(), mateVertex)
                            == visitedVertexes.end()){
                        graphicsScene->addLine(
                                    coords[vertex].first, coords[vertex].second,
                                    coords[mateVertex].first, coords[mateVertex].second,
                                    pen);
                        vertexQueue.push(mateVertex);
                    }
                }
            }
        }
    }

    qreal rad = 26;
    qreal indent = rad / 2.0;

    for(auto& pair: map){

        qreal x = coords[pair.first].first -indent;
        qreal y = coords[pair.first].second -indent;

        QGraphicsRectItem* item = new QGraphicsRectItem(x,y, rad, rad, nullptr);
        item->setBrush(QBrush(Qt::white));
        QGraphicsTextItem* textI = new QGraphicsTextItem(pair.first,item);
        textI->setPos(x,y-3);
        graphicsScene->addItem(item);
    }
}




