#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent, Qt::Window),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateImage()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //assume the directory exists and contains some files (otherwise should be specified in reqs?)
    //we want all jpg files, .tiff (not a .tif) and .bmp
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);

    QDir directory(dir);
    QStringList images = directory.entryList(QStringList()  << "*.jpg"
                                                            << "*.tiff"
                                                            << "*.bmp", QDir::Files);
    foreach(QString filename, images) {
        //put all file names into a container
        //(can be implemented in a separate thread if we have big amount of data)
        qDebug()<<filename;
        listOfFileNames.push_back(filename);
    }

    //show an image at once the folder was selected
    //and do mirroring on current image? (additional Req)
//  showImage();
}


void MainWindow::showImage()
{
    //show all images in containter then stop (or should be done in cicrle? issue Req)
    if (listOfFileNames.empty() == true)
        return;

    image.load(dir + "/" + listOfFileNames.pop());
    scene = new QGraphicsScene(this);
    scene->addPixmap(image);
    scene->setSceneRect(image.rect());

    ui->graphicsView->setScene(scene);
}

void MainWindow::on_pushButton_2_clicked()
{
    //RQ_4: update image every two seconds (optional Req: can be set)
    timer->start(2000);
}

void MainWindow::updateImage()
{
    showImage();
}

void MainWindow::on_pushButton_3_clicked()
{
    timer->stop();
}
