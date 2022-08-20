#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QTimer>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent, Qt::Window),
    ui(new Ui::MainWindow), selectedMode(0)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    timer = new QTimer(this);

    //bind timer with a slot to change an image
    connect(timer, SIGNAL(timeout()), this, SLOT(updateImage()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete timer;
}

void MainWindow::on_pushButton_clicked()
{
    //assume the directory exists and contains some files (otherwise should be specified in reqs?)
    //we want all jpg files, .tiff (not a .tif) and .bmp
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                QFileDialog::ShowDirsOnly
                                                |QFileDialog::DontResolveSymlinks
                                                |QFileDialog::DontUseNativeDialog);

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
  // showImage();
}


void MainWindow::showImage()
{
    //show all images in containter then stop (or should be done in cicrle? issue Req)
    if (listOfFileNames.empty() == true)
        return;

    QPixmap processedImage;
    image.load(dir + "/" + listOfFileNames.pop());

    switch (selectedMode) {
    case 0: //none
        processedImage = image;
        break;
    case 1: //horizontal
        processedImage = image.transformed(QTransform().scale(-1, 1));
        break;
    case 2: //vertical
        processedImage = image.transformed(QTransform().scale(1, -1));
        break;
    case 3: //both
        processedImage = image.transformed(QTransform().scale(-1, -1));
        break;
    default:
        break;
    }

    scene->clear();
    scene->addPixmap(processedImage);
    scene->setSceneRect(processedImage.rect());

    ui->graphicsView->setScene(scene);
    scene->update(ui->graphicsView->rect());
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

void MainWindow::on_comboBox_activated(int index)
{
    selectedMode = index;
}

void MainWindow::on_comboBox_activated(const QString &arg1)
{

}
