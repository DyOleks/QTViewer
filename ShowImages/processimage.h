#ifndef PROCESSIMAGE_H
#define PROCESSIMAGE_H

#include <QThread>
#include <QObject>
#include <QPixmap>

//!  A ProcessImage class.
/*!rocess one image p
  The class encapsulates a method to transform an image.
    The class expects to per thread.
*/
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
