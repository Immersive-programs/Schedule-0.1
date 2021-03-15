#include "mainschedule.h"
#include "ui_mainschedule.h"
#include "downloader.h"
#include "urldepartment.h"
#include "QDir"

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

using namespace QXlsx;

MainSchedule::MainSchedule(QWidget *parent): QMainWindow(parent), ui(new Ui::MainSchedule)
{
    ui->setupUi(this);
    ui->pushOfline->hide();

}

MainSchedule::~MainSchedule()
{
    delete ui;
}

void MainSchedule::DownloadError()
{
    ui->plainTextEdit->clear();
    ui->plainTextEdit->appendPlainText("ERROR: \n" + downloader->getError());

    QDate cd = QDate::currentDate();
    int dattod = cd.day();
    int datnex = cd.addDays(1).day();

    QDir dir(QDir::homePath()+"/ScheduleFolder/");
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); i++)
    {
        QFileInfo fi = list.at(i);
        if(fi.fileName().toInt() <= dattod-2 && fi.fileName().toInt() != 0)
        {
            QFile(fi.path()+"//"+fi.fileName()).remove();
        }

        if(fi.fileName().toInt() == dattod && fi.fileName().toInt() != 0)
        {
             datetoday = dattod;
             ui->pushButton_o->setEnabled(true);
        }

        if(fi.fileName().toInt() == datnex && fi.fileName().toInt() != 0)
        {
             datenextday = datnex;
             ui->pushButton_o->setEnabled(true);
        }
    }
}

void MainSchedule::DownloadComplete()
{
    ui->pushButton_o->setEnabled(false);
    ui->pushButton_t->setEnabled(false);
    ui->plainTextEdit->clear();

    QByteArray getfile = downloader->getData();

    Document xlsxR("y",getfile);

    QString date;
    bool isfind = false;
    if (xlsxR.load())
        {
            for (int i = 1; i < xlsxR.dimension().rowCount() ;i++ )
            {
                for (int v = 1; v < xlsxR.dimension().columnCount() ;v++ )
                {
                    Cell* cell = xlsxR.cellAt(i,v);
                    if ( cell != NULL )
                    {
                        if (cell->format().fontBold() && i == 2 && cell->readValue().toString() != "")
                        {
                            date = cell->readValue().toString();
                            ui->plainTextEdit->appendPlainText("Расписаниеы группы: " + group + " " + date);
                        }
                        if (cell->readValue().toString() == group)
                        {
                            isfind = true;
                            bool isvoid = false;
                            int u = i+1;
                            while (!isvoid)
                            {
                                Cell* ucell = xlsxR.cellAt(u,v);
                                Cell* zcell = xlsxR.cellAt(u,v-1);
                                if (ucell != NULL)
                                {
                                    QString qsell = ucell->readValue().toString();
                                    if(qsell.length() > 0)
                                    {
                                        ui->plainTextEdit->appendPlainText(qsell);

                                        if (zcell != NULL)
                                        {
                                            QString fsell = zcell->readValue().toString();
                                            if (fsell.length() > 1)
                                            {
                                                ui->plainTextEdit->appendPlainText("<<"+fsell+">>");
                                            }
                                        }
                                        u++;
                                    }
                                    else
                                    {
                                        isvoid = true;
                                    }
                                }
                                else
                                {
                                     isvoid = true;
                                }
                            }
                        }
                    }
                }
            }
        }

    int datget = date.remove(QRegExp("[^A-Za-z0-9_']")).toInt();
    QDate cd = QDate::currentDate();
    int dattod = cd.day();
    int datnex = cd.addDays(1).day();

    if (datget == dattod)
    {
        datetoday = datget;
        ui->pushButton_o->setEnabled(false);
    }
    if (datget == datnex)
    {
        datenextday = datget;
        ui->pushButton_t->setEnabled(false);
    }

    QDir dir(QDir::homePath()+"/ScheduleFolder/");
    QFileInfoList list = dir.entryInfoList();
    for (int i = 0; i < list.size(); i++)
    {
        QFileInfo fi = list.at(i);
        if(fi.fileName().toInt() <= dattod-2 && fi.fileName().toInt() != 0)
        {
            QFile(fi.path()+"//"+fi.fileName()).remove();
        }

        if(fi.fileName().toInt() == dattod && fi.fileName().toInt() != 0)
        {
             datetoday = dattod;
             ui->pushButton_o->setEnabled(true);
        }
    }

    QFile fileget(QDir::homePath()+"/ScheduleFolder/"+QString::number((datget)));
    if (!fileget.exists())
    {
        fileget.open(QIODevice::WriteOnly | QIODevice::Text);
        fileget.write(getfile);
        fileget.close();
    }

    if (!isfind)
    {
        ui->plainTextEdit->appendPlainText("Группа: \"" + group + "\" не найдена");
    }
}

void MainSchedule::readdocument(QString string)
{
    ui->plainTextEdit->clear();

    Document xlsxR(string);

    QString date;
    if (xlsxR.load())
    {
        for (int i = 1; i < xlsxR.dimension().rowCount() ;i++ )
        {
            for (int v = 1; v < xlsxR.dimension().columnCount() ;v++ )
            {
                Cell* cell = xlsxR.cellAt(i,v);
                if ( cell != NULL )
                {
                    if (cell->format().fontBold() && i == 2 && cell->readValue().toString() != "")
                    {
                        date = cell->readValue().toString();
                        ui->plainTextEdit->appendPlainText("Расписаниеы группы: " + group + " " + date);
                    }
                    if (cell->readValue().toString() == group)
                    {
                        bool isvoid = false;
                        int u = i+1;
                        while (!isvoid)
                        {
                            Cell* ucell = xlsxR.cellAt(u,v);
                            Cell* zcell = xlsxR.cellAt(u,v-1);
                            if (ucell != NULL)
                            {
                                QString qsell = ucell->readValue().toString();
                                if(qsell.length() > 0)
                                {
                                    ui->plainTextEdit->appendPlainText(qsell);

                                    if (zcell != NULL)
                                    {
                                        QString fsell = zcell->readValue().toString();
                                        if (fsell.length() > 1)
                                        {
                                            ui->plainTextEdit->appendPlainText("<<"+fsell+">>");
                                        }
                                    }
                                    u++;
                                }
                                else
                                {
                                    isvoid = true;
                                }
                            }
                            else
                            {
                                isvoid = true;
                            }
                        }
                    }
                }
            }
        }
    }
}

void MainSchedule::setGroup(QString setgroup)
{
    group = setgroup;
}

void MainSchedule::setDepartment(QString setdepartment)
{
    department = setdepartment.toInt();

    downloader = new Downloader();
    downloader->DowloadData(url.getURL(department));

    connect(downloader, &Downloader::onError, this, &MainSchedule::DownloadError);
    connect(downloader, &Downloader::onReady, this, &MainSchedule::DownloadComplete);
}


void MainSchedule::on_pushButton_o_clicked()
{
    ui->pushButton_o->setEnabled(false);
    ui->pushButton_t->setEnabled(true);
    readdocument(QDir::homePath()+"/ScheduleFolder/"+QString::number(datetoday));
}

void MainSchedule::on_pushButton_t_clicked()
{
    ui->pushButton_o->setEnabled(true);
    ui->pushButton_t->setEnabled(false);
    readdocument(QDir::homePath()+"/ScheduleFolder/"+QString::number(datenextday));
}

void MainSchedule::on_pushButton_newgroup_clicked()
{
    click--;
    if (click == 0)
    {
        QFile(QDir::homePath()+"/ScheduleFolder/goup").remove();
        QFile(QDir::homePath()+"/ScheduleFolder/department").remove();
        QFile(QDir::homePath()+"/ScheduleFolder/"+QString::number(datetoday)).remove();
        QFile(QDir::homePath()+"/ScheduleFolder/"+QString::number(datenextday)).remove();
        close();
    }
    else
    {
        ui->pushButton_newgroup->setText("нажмите ещё ("+ QString::number(click) +") раз для сброса...");
    }
}
