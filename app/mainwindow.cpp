#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // add img
    QPixmap pix(":/Images/SmartHome.png");
    ui->label_logo->setPixmap(pix.scaled(250,250,Qt::KeepAspectRatio));

}

MainWindow::~MainWindow()
{
    delete ui;
}

// Ham readPass **********************

QString readPassword(QString filename){
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << file.errorString();
        return 0;
    }
    QTextStream stream(&file);
    QString line = stream.readLine();
//    qInfo() << line;
    file.close();
    return line;
}

void MainWindow::on_pushButton_login_clicked()
{
    QString password = ui->lineEdit_password->text();
    if(password == readPassword(filename)){
//        QMessageBox::information(this, "Login", "Password is correct");
        hide();
        main_room = new class main_room(this);
        main_room->show();
        qInfo() << "Password is correct";
    }
    else{
        qInfo() << "Password is not correct";
        QMessageBox::information(this, "Login", "Password is not correct");
    }
}

