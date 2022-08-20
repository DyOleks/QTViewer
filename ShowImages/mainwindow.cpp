#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent, Qt::Window),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //assume the directory exists and contains some files (otherwise should be specified in reqs?)
    //we want all jpg files, .tiff (not a .tif) and .bmp
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    QDir directory(dir);
    QStringList images = directory.entryList(QStringList()  << "*.jpg"
                                                            << "*.tiff"
                                                            << "*.bmp", QDir::Files);
    foreach(QString filename, images) {
        //put all file names into container
        //(can be implemented in a separate thread if we have big abmount of data)
        qDebug()<<filename;
        listOfFileNames.push_back(filename);
    }
}
