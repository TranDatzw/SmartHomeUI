#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "main_room.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_login_clicked();

private:
    Ui::MainWindow *ui;
    main_room *main_room;
    QString filename = "D:/Study/N04_HK1/C++/Qt/app/filetext/text.txt";
};
#endif // MAINWINDOW_H
