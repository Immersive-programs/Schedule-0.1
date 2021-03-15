#ifndef MAINSCHEDULE_H
#define MAINSCHEDULE_H

#include <QMainWindow>
#include <downloader.h>
#include <urldepartment.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainSchedule; }
QT_END_NAMESPACE

class MainSchedule : public QMainWindow
{
    Q_OBJECT

public:
    MainSchedule(QWidget *parent = nullptr);
    ~MainSchedule();

    void DownloadError();
    void DownloadComplete();

    void setGroup(QString setgroup);
    void setDepartment(QString setdepartment);
    void readdocument(QString string);

private slots:
    void on_pushButton_o_clicked();

    void on_pushButton_t_clicked();

    void on_pushButton_newgroup_clicked();

private:
    int click = 3;
    int datetoday;
    int datenextday;
    int department;
    QString group;
    Ui::MainSchedule *ui;
    Downloader *downloader;
    urldepartment url;
};
#endif // MAINSCHEDULE_H
