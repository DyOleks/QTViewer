#ifndef LOADFILENAMESBCKGRND_H
#define LOADFILENAMESBCKGRND_H
#include <QObject>
#include <QThread>
#include <QDir>
#include <QDebug>
#include <QStringList>

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
