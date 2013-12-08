#ifndef MATLABPROC_H
#define MATLABPROC_H
#include <QProcess>
#include "creadingfile.h"
#include <QMainWindow>
#include <QTimer>
#include <QDir>

class CMatLabProc: public QMainWindow
{
    Q_OBJECT
private:
    QProcess proc;
    enum State {IDLE, ERROR, CALC};
    State state;
    QFileInfoList listFiles;
    QString pathToMat, pathToFile;

public:
    CMatLabProc(QString pathToMat, QString pathToFile, QFileInfoList listFiles);
    bool start();
    bool stop();
    bool readFromMatlab();

private slots:
    void stream();
    void err();
    void writeToMatlab();

//signals:
// void fin(QByteArray data);
};

#endif // MATLABPROC_H
