#include "cmatlabproc.h"
#include <iostream>

CMatLabProc::CMatLabProc(QString pathToMat, QString pathToFile, QFileInfoList listFiles)
{
    state = IDLE;
    this->listFiles= listFiles;
    this->pathToMat = pathToMat;
    this->pathToFile = pathToFile;
    path = listFiles.at(0).filePath();
    std::replace(path.begin(), path.end(), QChar('\\'), QChar('/'));
    openSlots();
}

bool CMatLabProc::start()
{
    QDir dir;
    newPathToFile = path;
    newPathToFile.replace(".mat", ".dat");

    QString str = pathToMat + " -nodisplay -nosplash -nodesktop  -noconsole -r \"Convert('"
            + dir.currentPath() + "\',\'"
            + path + "\',\'" + newPathToFile + "')\"";
    proc.start(str);

    if(proc.waitForStarted())
    {
        proc.closeWriteChannel();
        return true;
    }
    return false;
}

bool CMatLabProc::stop()
{
    proc.terminate();
}

void CMatLabProc::openSlots()
{
    QObject::connect(&proc, SIGNAL(readyReadStandardOutput()), (QObject*)this, SLOT(stream()));
    QObject::connect(&proc, SIGNAL(readyReadStandardError()), (QObject*)this, SLOT(err()));
}

void CMatLabProc::stream()
{
    if (proc.canReadLine())
    {
         QByteArray data = proc.readAllStandardOutput();
         //read numbers from data
         if (data.end())
         {
             //proc.closeReadChannel(QProcess::StandardOutput);
             proc.disconnect();
 //            emit fin(data);
         }
    }


    if(!newPathToFile.isEmpty())
    {
        CReadingFile* file = new CReadingFile(newPathToFile);
    }

    stop();
}

void CMatLabProc::err()
{
    if (proc.canReadLine())
    {
        QByteArray data = proc.readAllStandardError();
        proc.closeReadChannel(QProcess::StandardError);
        proc.disconnect();
        state = ERROR;
    }
}

//void CMatLabProc::fin(QByteArray data)
//{
//    CReadingFile* file = new CReadingFile(QString::fromAscii(data));
//}
