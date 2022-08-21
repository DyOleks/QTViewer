#include "processimage.h"
#include <QDebug>


// override the QThread's run() method
ProcessImage::ProcessImage(QObject *parent)
{

}

void ProcessImage::run()
{
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
}

void ProcessImage::setMode(int mode)
{
    this->selectedMode = mode;
}

void ProcessImage::setImageName(QString imageName)
{
    this->image.load(imageName);
}

QPixmap ProcessImage::getProcessedImage()
{
    return processedImage;
}
