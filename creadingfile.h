#ifndef CREADINGFILE_H
#define CREADINGFILE_H

#include <QString>

class CReadingFile
{
public:
    CReadingFile(QString data);
private:
    void parseData(QString data);
};

#endif // CREADINGFILE_H
