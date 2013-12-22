#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include <QMainWindow>
#include "creadingfile.h"
#include <QFileDialog>
#include <QDir>
#include "cmatlabproc.h"

namespace Ui {
class CMainWindow;
}

class CMainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit CMainWindow(QWidget *parent = 0);
    ~CMainWindow();
    
private slots:
    void on_buttonBrowse_clicked();

    void on_buttonBrowseMat_clicked();

    void on_buttonCovert_clicked();

private:
    Ui::CMainWindow *ui;
    QString fileName;
    QString fileMatlab;
    QFileInfoList listFiles;
    void contentList(QString fileName);
};

#endif // CMAINWINDOW_H
