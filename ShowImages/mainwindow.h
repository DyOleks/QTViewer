#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QStringList>
#include <QGraphicsScene>
#include "loadfilenamesbckgrnd.h"
#include "processimage.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void showImage();

public slots:
        void getLoadinglistOfFileNames(QStringList listFileNames);

private slots:
    void updateImage();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_comboBox_activated(int index);

signals:
    void startLoadingFileNamesBackground(QString sPath);

private:
    Ui::MainWindow *ui;
    QStringList listOfFiles; //just keep all file names to fill stack again
    QGraphicsScene *scene;
    QPixmap processedImage;
    QString dir;
    QTimer *timer;
    int selectedMode;
    LoadFileNamesBckgrnd *loadFileNames;
    QThread *thread;
    ProcessImage *processImage;
    QThread *threadImage;
    int index;
};

#endif // MAINWINDOW_H
