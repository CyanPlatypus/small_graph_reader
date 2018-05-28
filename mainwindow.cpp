#include "mainwindow.h"
#include "graphsubwindow.h"
#include "ui_mainwindow.h"
#include "testwin.h"

#include <QtCore>
#include <QtWidgets>

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

void MainWindow::CreateGraphSubWindow(QString title, QString text){
    GraphSubWindow *subWindow = new GraphSubWindow(ui->mdiArea, text);
    subWindow->setAttribute(Qt::WA_DeleteOnClose);
    subWindow->setWindowTitle(title);
    subWindow->show();
}

void MainWindow::OnOpenClick() {
    qDebug()<<"Open clicked.";
//    QMessageBox msgBox;
//    msgBox.setText("The document has been modified.");
//    msgBox.setInformativeText("Do you want to save your changes?");
//    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
//    msgBox.setDefaultButton(QMessageBox::Save);
//    int ret = msgBox.exec();
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
