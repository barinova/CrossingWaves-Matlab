#include "creadingfile.h"

CReadingFile::CReadingFile(QString pathToFile)
{
    QFile file(pathToFile);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug("Error: reading file");
    }
    else
    {
        parseData(&file);
    }
}

void CReadingFile::parseData(QFile* file)
{
    QTextStream in(file);
    QString tmp;
    QStringList fields;
    int i;
    while(!in.atEnd())
    {
        listOfData.countX = atof(in.readLine().toStdString().c_str());
        listOfData.countT = atof(in.readLine().toStdString().c_str());
        tmp = in.readLine();

        fields = tmp.split(" ");
    }

    for(i = 0; i < listOfData.countX; i++)
    {
        listOfData.x.append(atof(fields.at(i).toStdString().c_str()));
    }

    for(i; i < listOfData.countT + listOfData.countT; i++)
    {
        listOfData.t.append(atof(fields.at(i - listOfData.countX).toStdString().c_str()));
    }
     //if()
     //    return true;
    // else
      //   return false;
}
