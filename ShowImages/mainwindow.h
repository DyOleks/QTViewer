#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QGraphicsScene>


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

private slots:
    void updateImage();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_comboBox_activated(const QString &arg1);
    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
    QStack<QString> listOfFileNames;
    QGraphicsScene *scene;
    QPixmap image;
    QString dir;
    QTimer *timer;
    int selectedMode;
};

#endif // MAINWINDOW_H
