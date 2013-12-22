#ifndef CREADINGFILE_H
#define CREADINGFILE_H

#include <QString>
#include <QTextStream>
#include <QStringList>
#include <QFile>

struct dat
{
    int countX;
    int countT;
    QList<float> x;
    QList<float> t;
};

class CReadingFile
{
public:
    CReadingFile(QString pathToFile);
private:
    void parseData(QFile *file);
    dat listOfData;
};

#endif // CREADINGFILE_H
