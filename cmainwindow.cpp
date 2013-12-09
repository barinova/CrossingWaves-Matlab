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

    std::replace( fileName.begin(), fileName.end(), QChar('\\'), QChar('/') );
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
    QStringList nameFilter;
    QDir dir(fileName);// = new QDir();
    nameFilter << "*.mat";

    listFiles = dir.entryInfoList(nameFilter, QDir::Files);
}
