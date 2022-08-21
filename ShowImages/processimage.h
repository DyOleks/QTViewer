#ifndef PROCESSIMAGE_H
#define PROCESSIMAGE_H

#include <QThread>
#include <QObject>
#include <QPixmap>


class ProcessImage : public QThread
{
    Q_OBJECT
public:
    explicit ProcessImage(QObject *parent = nullptr);
    void run();

    void setMode(int mode);
    void setImageName(QString imageName);
    QPixmap getProcessedImage();
signals:

public slots:

private:
    int selectedMode;
    QPixmap image;
    QPixmap processedImage;
};

#endif // PROCESSIMAGE_H
