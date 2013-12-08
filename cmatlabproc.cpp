#include "cmatlabproc.h"

CMatLabProc::CMatLabProc(QString pathToMat, QString pathToFile, QFileInfoList listFiles)
{
    state = IDLE;
    this->listFiles= listFiles;
    this->pathToMat = pathToMat;
    this->pathToFile = pathToFile;
}

bool CMatLabProc::start()
{
   //QObject::connect(&proc, SIGNAL(started()), (QObject*)this, SLOT(writeToMatlab()));
    QString str = pathToMat + "-r cd " + pathToFile
            + ", try, run('" + pathToFile + "/"
            + listFiles.at(0).baseName() + "'); end; quit";
    proc.startDetached(str);
    if(proc.waitForStarted())
    {
       // QTimer::singleShot(10000, this, SLOT(writeToMatlab()));
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
         QByteArray script = "clear;\n"
                 "load " + pathToFile.toAscii() +"\n"
                 "x\n";
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
