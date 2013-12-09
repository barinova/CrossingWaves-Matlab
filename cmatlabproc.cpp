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
}

bool CMatLabProc::start()
{
    QString str = pathToMat + " -nodisplay -nosplash -nodesktop -r \"load('" +
            path + "')\";";
    proc.start(str);

    if(proc.waitForStarted())
    {

        QByteArray script = "x\n";

        proc.write(script);
        writeToMatlab();
        return true;
    }
    return false;
}

bool CMatLabProc::stop()
{

}

void CMatLabProc::writeToMatlab()
{
    //if (state != IDLE)
    //{
         state = CALC;
         QByteArray script = "x\n";
         proc.write(script);
         proc.closeWriteChannel();
         QObject::connect(&proc, SIGNAL(readyReadStandardOutput()), (QObject*)this, SLOT(stream()));
         QObject::connect(&proc, SIGNAL(readyReadStandardError()), (QObject*)this, SLOT(err()));
   // }
}

void CMatLabProc::stream()
{
    if (proc.canReadLine())
    {
         QByteArray data = proc.readAllStandardOutput();
         //read numbers from data
         if (data.end())
         {
             proc.closeReadChannel(QProcess::StandardOutput);
             proc.disconnect();
             state = IDLE;
 //            emit fin(data);
         }
    }
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
