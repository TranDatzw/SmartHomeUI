#include "change_password.h"
#include "ui_change_password.h"
#include "main_room.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

change_password::change_password(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::change_password)
{
    ui->setupUi(this);
}

change_password::~change_password()
{
    delete ui;
}

void change_password::on_logout_password_Btn_clicked()
{
    hide();
    main_room *main_room;
    main_room = new class main_room(this);
    main_room->show();
}

QString read_changePassword(QString filename){
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

bool writePassword(QString filename, QString new_password){
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        qCritical() << file.errorString();
        return false;
    }
    QTextStream stream(&file);
    stream << new_password;
    file.close();
    return true;
}

void change_password::on_save_password_Btn_clicked()
{
    QString old_password = ui->old_pw_line_edit->text();
    QString new_password = ui->new_pw_line_edit->text();
    QString confirm_password = ui->confirm_pw_line_edit->text();
    if(read_changePassword(filename) != old_password){
        qInfo() << "Old password not is correct";
        QMessageBox::information(this, "Old password", "Old password not is correct");
    }
    else{
        if(new_password == confirm_password){
            writePassword(filename, new_password);
            qInfo() << "Change password successfully";
            qInfo() << read_changePassword(filename);
            QMessageBox::information(this, "Change Password", "Change password successfully");
        }else{
            qInfo() << "Confirm password not is correct";
            QMessageBox::information(this, "Change Password", "Confirm password not is correct");
        }
    }
}

