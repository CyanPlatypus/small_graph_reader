#include "graphsubwindow.h"
#include "ui_graphsubwindow.h"
#include "graphmanager.h"

#include <QMdiSubWindow>
#include <QtCore>
#include <QtWidgets>

GraphSubWindow::GraphSubWindow(QWidget *parent) :
    QMdiSubWindow(parent),
    ui(new Ui::GraphSubWindow)
{
    ui->setupUi(this);
    setWidget(ui->widget);
}

GraphSubWindow::GraphSubWindow(QWidget *parent, QString& inputText) :
    QMdiSubWindow(parent),
    ui(new Ui::GraphSubWindow)
{
    ui->setupUi(this);
    setWidget(ui->widget);
    ui->inputTextEdit->setPlainText(inputText);
}

GraphSubWindow::~GraphSubWindow()
{
    delete ui;
}

void GraphSubWindow::Proceed(){
    qDebug()<<"Start clicked.";
    ui->outputTextEdit->clear();
    ui->outputTextEdit
            ->setPlainText(
                GraphManager::FindConnectedComponents(
                    ui->inputTextEdit->toPlainText()));

}

void GraphSubWindow::Save(){
    qDebug()<<"Save clicked.";
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                               "", tr("Text File (*.txt)"));
    QFile qSaveFile(fileName);
    if(qSaveFile.open(QFile::WriteOnly)){
        QTextStream ts(&qSaveFile);
        ts << ui->outputTextEdit->toPlainText();
        qSaveFile.close();
    }

}
