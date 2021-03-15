#ifndef GROUPWINDOW_H
#define GROUPWINDOW_H

#include <QMainWindow>
#include <urldepartment.h>
#include <downloader.h>

namespace Ui {
class GroupWindow;
}

class GroupWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit GroupWindow(QWidget *parent = nullptr);
    ~GroupWindow();

    void DownloadError();
    void DownloadComplete();

    QString getGroup();
    void setGroup(QString setgroup);
    QString getDepartment();
    void setDepartment(QString setdepartment);

private slots:
    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

private:

    void CreateGroups(QByteArray qbytearray);
    QString group;
    QString department;
    Downloader *downloader;
    int _index;
    Ui::GroupWindow *ui;
    urldepartment url;
    QByteArray file[4];
};

#endif // GROUPWINDOW_H
