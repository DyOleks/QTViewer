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


    //make loading filenames in a separate thread (non-functional requirement RQ_4)
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
    //assume the directory exists and contains some files (is it assumed > Req)
    dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                QFileDialog::ShowDirsOnly
                                                |QFileDialog::DontResolveSymlinks
                                                |QFileDialog::DontUseNativeDialog);

    emit startLoadingFileNamesBackground(dir);

    //show an image at once the folder was selected
    //and do mirroring on current image? (additional > Req)
}


void MainWindow::showImage()
{
    //show all images in containter then stop (or should be done in cicrle > Req)
    if (index == 0)
    {
        //return;
        index = listOfFiles.count() - 1;    //reloading, let's look at the pictures from the beginning
    }

    QString fullPath = dir + "/" + listOfFiles.at(index--);


    //make image processing in a separate thread (non-functional requirement RQ_4)
    ProcessImage threadProcessImage;

    qDebug() << "GUI thread before MyThread start()"
                << threadProcessImage.currentThreadId();

    threadProcessImage.setMode(selectedMode);
    threadProcessImage.setImageName(fullPath);

    threadProcessImage.start();

    qDebug() << "GUI thread after start()"
                << threadProcessImage.currentThreadId();

    threadProcessImage.wait();
    processedImage = threadProcessImage.getProcessedImage();


    //TODO: can be improved
    scene->clear();
    scene->addPixmap(processedImage);
    scene->setSceneRect(processedImage.rect());

    ui->graphicsView->setScene(scene);
    scene->update(ui->graphicsView->rect());

}

void MainWindow::getLoadinglistOfFileNames(QStringList listFileNames)
{
    foreach (const QString &str, listFileNames) {
        listOfFiles.push_back(str);
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

