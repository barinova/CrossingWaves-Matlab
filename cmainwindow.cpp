#include "cmainwindow.h"
#include "ui_cmainwindow.h"

CMainWindow::CMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CMainWindow)
{
    ui->setupUi(this);
}

CMainWindow::~CMainWindow()
{
    delete ui;
}

void CMainWindow::on_buttonBrowse_clicked()
{
   fileName =  QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
   // fileName = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("MAT Files (*.mat)"));
    ui->fileNameEdit->setText(fileName);
    contentList(fileName);
}

void CMainWindow::on_buttonCalculate_clicked()
{
    if(fileName != "" && fileMatlab != "" && !listFiles.empty())
    {
        CMatLabProc* mat = new CMatLabProc("\"" + fileMatlab + "\"", fileName, listFiles);
        mat->start();
    }
}

void CMainWindow::on_buttonBrowseMat_clicked()
{
    fileMatlab = QFileDialog::getOpenFileName(this, tr("Open File"),"/path/to/file/",tr("EXE Files (*.exe)"));
    ui->fileNameEditMat->setText(fileMatlab);
}

void CMainWindow::contentList(QString fileName)
{
    QDir dir;// = new QDir();
    //dir->setNameFilters(QStringList()<<"*.mat");
    listFiles = dir.entryInfoList();
}
