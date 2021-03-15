#include "urldepartment.h"
#include "QObject"

urldepartment::urldepartment(QObject *parent): QObject(parent)
{

}

QString urldepartment::getURL(const int num)
{
    const QString urls[4]
    {
        "http://www.bgtc.su/wp-content/uploads/raspisanie/zamena1k.xlsx",
        "http://www.bgtc.su/wp-content/uploads/raspisanie/zamena2k.xlsx",
        "http://www.bgtc.su/wp-content/uploads/raspisanie/zamena3k.xlsx",
        "http://www.bgtc.su/wp-content/uploads/raspisanie/zamena4k.xlsx"
    };
    return urls[num-1];
}
