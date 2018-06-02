#include "mainwindow.h"
#include "graphsubwindow.h"
#include "ui_mainwindow.h"
#include "testwin.h"

#include <QtCore>
#include <QtWidgets>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mdiArea->setViewMode(QMdiArea::TabbedView);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::CreateGraphSubWindow(const QString& title, const QString& text){
    GraphSubWindow *subWindow = new GraphSubWindow(ui->mdiArea, text);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowTitle(title);
    subWindow->show();
}

void MainWindow::OnOpenClick() {
    qDebug()<<"Open clicked.";
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"),"", tr("Text Files (*.txt)"));

    QFile qFile(fileName);
    if (qFile.open(QFile::ReadOnly /*| QFile::Text*/)){
        QTextStream ts(&qFile);
        QString text = qFile.readAll();
        qFile.close();
        QFileInfo fileInfo(fileName);
        CreateGraphSubWindow(fileInfo.fileName(), text);
    }
}

void MainWindow::OnNewClick(){
    qDebug()<<"New clicked.";
    CreateGraphSubWindow("title", "");
}

void MainWindow::OnFindComponentsClick(){
    qDebug()<<"Find clicked.";

    GraphSubWindow* grSubWind = GetGraphSubWindow();
    if (grSubWind!= nullptr){
        std::map<QString, QString> nameText = grSubWind->Proceed();
        for(auto& tab : nameText){
            CreateGraphSubWindow(tab.first, tab.second);
        }
    }
}

void MainWindow::OnSaveClick(){
    qDebug()<<"Save clicked.";

    GraphSubWindow* grSubWind = GetGraphSubWindow();
    if (grSubWind!= nullptr){

        QString fileName = QFileDialog::getSaveFileName(
                    this, tr("Save File"),"", tr("Text File (*.txt)"));
        QFile qSaveFile(fileName);
        if(qSaveFile.open(QFile::WriteOnly)){
            QTextStream ts(&qSaveFile);
            ts << grSubWind->Save();
            qSaveFile.close();
        }
    }
}

GraphSubWindow* MainWindow::GetGraphSubWindow(){
    if(SubWindowExists())
        return dynamic_cast<GraphSubWindow*>(ui->mdiArea->currentSubWindow());
    else{
        QMessageBox::information(0, "Error", "No window selected.");
        return nullptr;
    }
}

bool MainWindow::SubWindowExists(){
    return (ui->mdiArea->subWindowList().count() != 0);
}

