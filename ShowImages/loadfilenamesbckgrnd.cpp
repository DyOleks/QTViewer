#include "loadfilenamesbckgrnd.h"

LoadFileNamesBckgrnd::LoadFileNamesBckgrnd(QObject *parent) : QObject(parent)
{

}

void LoadFileNamesBckgrnd::runLoadingFileNamesBackground(QString sPath)
{
    QDir directory(sPath);

    //we want all jpg files, .tiff (not a .tif) and .bmp
    QStringList images = directory.entryList(QStringList()  << "*.jpg"
                                                            << "*.tiff"
                                                            << "*.bmp", QDir::Files);
    foreach(QString filename, images) {
        //put all file names into a container
        //(can be implemented in a separate thread if we have big amount of data)
        qDebug()<<filename;
        listOfFileNamesLocal.push_back(filename);
    }

    //return results
    emit finishedLoadinglistOfFileNames(listOfFileNamesLocal);
}

