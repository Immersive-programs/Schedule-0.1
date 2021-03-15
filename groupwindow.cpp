#include "groupwindow.h"
#include "ui_groupwindow.h"
#include "QDebug"

#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

using namespace QXlsx;

#include "downloader.h"
#include "urldepartment.h"

GroupWindow::GroupWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GroupWindow)
{
    ui->setupUi(this);
    ui->label_er->hide();
}

GroupWindow::~GroupWindow()
{
    delete ui;
}

void GroupWindow::on_comboBox_activated(int index)
{
   _index = index;
   if (index != 0)
   {
       if (file[index-1].length() < 1)
       {
           downloader = new Downloader();
           downloader->DowloadData(url.getURL(index));
           connect(downloader, &Downloader::onError, this, &GroupWindow::DownloadError);
           connect(downloader, &Downloader::onReady, this, &GroupWindow::DownloadComplete);
       }
       else
       {
           CreateGroups(file[index-1]);
       }
   }
   else
   {
       ui->comboBox_2->clear();
   }
}

void GroupWindow::DownloadError()
{
    ui->label_er->show();
    ui->label_er->setText("Ошибка: "+downloader->getError());
}

void GroupWindow::CreateGroups(QByteArray qbytearray)
{
    ui->comboBox_2->clear();

    Document xlsxR("badfile",qbytearray);

    if (xlsxR.load()) // load excel file
    {
        for (int i = 1; i < xlsxR.dimension().rowCount() ;i++ )
        {
            for (int v = 1; v < xlsxR.dimension().columnCount() ;v++ )
            {
                Cell* cell = xlsxR.cellAt(i,v);
                if ( cell != NULL && cell->format().fontBold() && cell->format().fontUnderline())
                {
                    QString valve = cell->readValue().toString();
                    if (valve.length() > 3) ui->comboBox_2->addItem(valve);
                }
            }
        }
    }
}

void GroupWindow::DownloadComplete()
{
    QByteArray get = downloader->getData();
    file[_index-1] = get;
    CreateGroups(get);
}

void GroupWindow::on_pushButton_clicked()
{
    QString combox2 = ui->comboBox_2->currentText();
    if (combox2.length() == 0)
    {
        ui->label_er->show();
        ui->label_er->setText("Ошибка: Не выбранна группа");
    }
    else
    {
        ui->label_er->hide();
        setGroup(combox2);
        setDepartment(QString::number(_index));
        this->close();
    }
}

QString GroupWindow::getGroup()
{
    return group;
}

void GroupWindow::setGroup(QString setgroup)
{
    group = setgroup;
}

QString GroupWindow::getDepartment()
{
    return department;
}

void GroupWindow::setDepartment(QString setdepartment)
{
    department = setdepartment;
}
