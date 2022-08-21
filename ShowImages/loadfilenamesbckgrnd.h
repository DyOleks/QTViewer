#ifndef LOADFILENAMESBCKGRND_H
#define LOADFILENAMESBCKGRND_H
#include <QObject>
#include <QThread>
#include <QDir>
#include <QDebug>
#include <QStringList>

//!  A LoadFileNamesBckgrnd class.
/*!
  The class encapsulates a method of all files
    loading in a folder. Then it emits a signal
    with the list of file names
*/
class LoadFileNamesBckgrnd : public QObject
{
    Q_OBJECT
public:
    explicit LoadFileNamesBckgrnd(QObject *parent = nullptr);

signals:
    void finishedLoadinglistOfFileNames(QStringList listFileNames);
public slots:
    void runLoadingFileNamesBackground(QString sPath);

private:
    QStringList listOfFileNamesLocal;
};

#endif // LOADFILENAMESBCKGRND_H
