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

    thread = new QThread(this);
    connect(this, SIGNAL(destroyed()), thread, SLOT(quit()));

    loadFileNames = new LoadFileNamesBckgrnd();
    //bind signal (MainWindow) to slot (loadFileNamesBckgrnd) of thread to load file names from folder
    connect(this, SIGNAL(startLoadingFileNamesBackground(QString )),
            loadFileNames, SLOT(runLoadingFileNamesBackground(QString)));
    //bind signal (loadFileNamesBckgrnd) of thread to slot (MainWindow) to return results (file names from folder)
    connect(loadFileNames, SIGNAL(finishedLoadinglistOfFileNames(QStringList)),
            this, SLOT(getLoadinglistOfFileNames(QStringList)));

    loadFileNames->moveToThread(thread);
    thread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
    delete timer;
    thread->deleteLater();
}

void MainWindow::on_pushButton_clicked()
{
    //assume the directory exists and contains some files
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                QFileDialog::ShowDirsOnly
                                                |QFileDialog::DontResolveSymlinks
                                                |QFileDialog::DontUseNativeDialog);

    emit startLoadingFileNamesBackground(dir);

    //show an image at once the folder was selected
    //and do mirroring on current image? (additional Req)
}


void MainWindow::showImage()
{
    //show all images in containter then stop (or should be done in cicrle? issue Req)
    if (listOfFileNames.empty() == true)
        return;

    QPixmap processedImage;
    image.load(dir + "/" + listOfFileNames.pop());

    switch (selectedMode) {
    case 1: //horizontal
        processedImage = image.transformed(QTransform().scale(-1, 1));
        break;
    case 2: //vertical
        processedImage = image.transformed(QTransform().scale(1, -1));
        break;
    case 3: //both
        processedImage = image.transformed(QTransform().scale(-1, -1));
        break;

    case 0: //none
        [[fallthrough]]; //C++17
    default:
        processedImage = image;
        break;
    }

    scene->clear();
    scene->addPixmap(processedImage);
    scene->setSceneRect(processedImage.rect());

    ui->graphicsView->setScene(scene);
    scene->update(ui->graphicsView->rect());
}

void MainWindow::getLoadinglistOfFileNames(QStringList listFileNames)
{
    foreach (const QString &str, listFileNames) {
        listOfFileNames.push_back(str);
    }
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

