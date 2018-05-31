#include "graphsubwindow.h"
#include "ui_graphsubwindow.h"
#include "graphmanager.h"

#include <QMdiSubWindow>
#include <QtCore>
#include <QtWidgets>

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
}


GraphSubWindow::~GraphSubWindow()
{
    delete ui;
}

map<QString, QString> GraphSubWindow::Proceed(){
//    qDebug()<<"Start clicked.";
//    ui->outputTextEdit->clear();
//    ui->outputTextEdit
//            ->setPlainText(
//                GraphManager::FindConnectedComponents(
//                    ui->inputTextEdit->toPlainText()));

    return graphManager->FindConnectedComponents();

}


QString GraphSubWindow::Save(){
    return graphManager->Export();
}
