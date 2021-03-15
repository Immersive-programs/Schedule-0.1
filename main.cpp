#include "mainschedule.h"
#include "groupwindow.h"

#include <QApplication>

#include <QStandardPaths>
#include <QDir>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QDir dir(QDir::homePath());
    if(!dir.exists("ScheduleFolder"))
    {
       dir.mkdir("ScheduleFolder");
    }
    QFile filegoup (QDir::homePath()+"/ScheduleFolder/goup");
    QFile filedepartment (QDir::homePath()+"/ScheduleFolder/department");
    if(!filegoup.exists() || !filedepartment.exists())
    {
        GroupWindow d;
        d.show();
        a.exec();
        QString q = d.getGroup();
        QString f = d.getDepartment();
        if (q != "" && f != "")
        {
            filegoup.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out1(&filegoup);
            out1 << q;
            filegoup.close();

            filedepartment.open(QIODevice::WriteOnly | QIODevice::Text);
            QTextStream out2(&filedepartment);
            out2 << f;
            filedepartment.close();

            MainSchedule w;
            w.setGroup(q);
            w.setDepartment(f);
            w.show();
            return a.exec();
        }
    }
    else
    {
        MainSchedule w;

        filegoup.open(QIODevice::ReadOnly | QIODevice::Text);
        w.setGroup(filegoup.readAll());
        filegoup.close();

        filedepartment.open(QIODevice::ReadOnly | QIODevice::Text);
        w.setDepartment(filedepartment.readAll());
        filedepartment.close();

        w.show();
        return a.exec();
    }
}
