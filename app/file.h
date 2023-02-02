#ifndef FILE_H
#define FILE_H
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>


class file
{
public:
    file();
private slots:
    int sumLineFile();
    QString read_statusFile();
    bool write_status();
private:
    QString filename;
};

#endif // FILE_H
