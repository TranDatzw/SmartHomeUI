#include "bed_room.h"
#include "ui_bed_room.h"
#include "main_room.h"
#include <QPixmap>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

// **File

int sumLineFile_bed(QString filename, QString line[], int &sumline){
    QFile file(filename);
    sumline = 0;
    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << file.errorString();
        return 0;
    }
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        line[sumline] = stream.readLine();
        sumline++;
    }
    file.close();
    return sumline;
}

QString read_statusFile_bed(QString filename, QString line[], int &i, int location){
    QFile file(filename);
    i = 0;
    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << file.errorString();
        return 0;
    }
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        line[i] = stream.readLine(); // doc 1 dong`
        i++;
    }
    file.close();
    return line[location];
}

// ****************************************************

bed_room::bed_room(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bed_room)
{
    ui->setupUi(this);

    sumline = sumLineFile_bed(filename, line, sumline);
    readStatuswhenWrite();
}

bed_room::~bed_room()
{
    delete ui;
}

// *File

bool write_status_bed(QString filename, QString line[], int i, int sumline, QString status, int location){
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        qCritical() << file.errorString();
        return false;
    }

    QTextStream stream(&file);
    for(int j = 0; j < sumline ; j++){
        if(j < location){
            stream << read_statusFile_bed(filename, line, i, j) << Qt::endl;
        }
        else if(j == location){
             stream << status << Qt::endl;
        }
        else{
            stream << read_statusFile_bed(filename, line, i, j) << Qt::endl;
        }
    }
    file.close();
    return true;
}

//*****************************************************

// *PC

void bed_room::on_On_TV_Btn_clicked()
{
    QPixmap fb(":/Images/PC_on_fb.png");
    QPixmap instagram(":/Images/PC_on_Instagram.png");
    QPixmap tiktok(":/Images/PC_on_tiktok.png");
    QPixmap youtube(":/Images/PC_on_youtube.png");
    QPixmap computer(":/Images/computer_on.png");
    QString status = "On";
    if(KenhTV == 0){
       qInfo() << "Dang bat Facebook";
       ui->TV_label->setPixmap(fb.scaled(300,300,Qt::KeepAspectRatio));
    }else if(KenhTV == 1){
        qInfo() << "Dang bat Instagram";
        ui->TV_label->setPixmap(instagram.scaled(300,300,Qt::KeepAspectRatio));
    }else if(KenhTV == 2){
        qInfo() << "Dang bat Tiktok";
        ui->TV_label->setPixmap(tiktok.scaled(300,300,Qt::KeepAspectRatio));
    }else if(KenhTV == 3){
        qInfo() << "Dang bat Youtube";
        ui->TV_label->setPixmap(youtube.scaled(300,300,Qt::KeepAspectRatio));
    }else{
        qInfo() << "Dang bat PC";
        ui->TV_label->setPixmap(computer.scaled(300,300,Qt::KeepAspectRatio));
    }
    write_status_bed(filename, line, i, sumline, status, 2);
}

void bed_room::on_Off_TV_Btn_clicked()
{
    QString status = "Off";
    qInfo() << "Da tat PC";
    QPixmap bed(":/Images/computer_off.png");
    ui->TV_label->setPixmap(bed.scaled(300,300,Qt::KeepAspectRatio));
    write_status_bed(filename, line, i, sumline, status, 2);
}

void bed_room::on_up_volume_Btn_clicked()
{
    if(read_statusFile_bed(filename, line, i, 2) == "On"){
        TV++;
        qInfo() << "Volume PC: " << TV;
    }
    else{
        qInfo() << "Volume chua duoc bat!!!";
    }
    QString status = QString::number(TV);
    write_status_bed(filename, line, i, sumline, status, 4);
    ui->progressBar_TV->setValue(TV);
}

void bed_room::on_down_volume_Btn_clicked()
{
    ui->progressBar_TV->setValue(TV);
    if(read_statusFile_bed(filename, line, i, 2) == "On"){
        TV--;
        qInfo() << "Volume PC: " << TV;
    }
    else{
        qInfo() << "Volume chua duoc bat!!!";
    }
    QString status = QString::number(TV);
    write_status_bed(filename, line, i, sumline, status, 4);
    ui->progressBar_TV->setValue(TV);
}

void bed_room::on_TV_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void bed_room::on_previus_TV_Btn_clicked()
{
    if(read_statusFile_bed(filename, line, i, 2) == "On"){
        if(KenhTV > 0 && KenhTV < 4)
           KenhTV--;
        else{
           KenhTV = 3;
        }
        on_On_TV_Btn_clicked();
    }else{
        qInfo() << "TV chua duoc bat";
    }
}

void bed_room::on_next_volume_Btn_clicked()
{
    if(read_statusFile_bed(filename, line, i, 2) == "On"){
        if(KenhTV >= 0 && KenhTV < 3)
           KenhTV++;
        else{
           KenhTV = 0;
        }
        on_On_TV_Btn_clicked();
    }
    else{
        qInfo() << "TV chua duoc bat";
    }
}

// **************************************8

// * May Lanh

void bed_room::on_AC_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void bed_room::on_On_AC_Btn_clicked()
{
    QString status = "On";
    if(read_statusFile_bed(filename, line, i, 7) == "Off"){
        qInfo() << "May lanh dang bat";
    }
    QPixmap bed(":/Images/AC_on.png");
    ui->AC_label->setPixmap(bed.scaled(300,300,Qt::KeepAspectRatio));
    write_status_bed(filename, line, i, sumline, status, 7);
}

void bed_room::on_Off_AC_Btn_clicked()
{
    QString status = "Off";
    qInfo() << "Da tat May Lanh";
    QPixmap bed(":/Images/AC_off.png");
    ui->AC_label->setPixmap(bed.scaled(300,300,Qt::KeepAspectRatio));
    write_status_bed(filename, line, i, sumline, status, 7);
}

void bed_room::on_up_AC_Btn_clicked()
{
    if(read_statusFile_bed(filename, line, i, 7) == "On"){
        temp++;
        qInfo() << "Nhiet do May Lanh :" << temp;
    }
    else{
        qInfo() << "May lanh chua duoc bat";
    }
    QString status = QString::number(temp); // chuyen in sang string
    write_status_bed(filename, line, i, sumline, status, 9);
    ui->Temp_label->setText(QString("Temp = %1 °C").arg(temp));
}

void bed_room::on_down_AC_Btn_clicked()
{
    if(read_statusFile_bed(filename, line, i, 7) == "On"){
        temp--;
        qInfo() << "Nhiet do May Lanh :" << temp;
    }
    else{
        qInfo() << "May lanh chua duoc bat";
    }
    QString status = QString::number(temp); // chuyen in sang string
    write_status_bed(filename, line, i, sumline, status, 9);
    ui->Temp_label->setText(QString("Temp = %1 °C").arg(temp));
}

//******************************************

// Lamp

void bed_room::on_LAMP_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void bed_room::on_On_LAMP_Btn_clicked()
{
    if(read_statusFile_bed(filename, line, i, 12) == "Off"){
        qInfo() << "Den dang bat";
    }
    QPixmap blue1(":/Images/Lamp_on_blue_1.png");
    QPixmap blue2(":/Images/Lamp_on_blue_2.png");
    QPixmap blue3(":/Images/Lamp_on_blue_3.png");
    QPixmap blue4(":/Images/Lamp_on_blue_4.png");
    QPixmap blue5(":/Images/Lamp_on_blue_5.png");
    QPixmap red1(":/Images/Lamp_on_red_1.png");
    QPixmap red2(":/Images/Lamp_on_red_2.png");
    QPixmap red3(":/Images/Lamp_on_red_3.png");
    QPixmap red4(":/Images/Lamp_on_red_4.png");
    QPixmap red5(":/Images/Lamp_on_red_5.png");
    QPixmap yellow1(":/Images/Lamp_on_yellow_1.png");
    QPixmap yellow2(":/Images/Lamp_on_yellow_2.png");
    QPixmap yellow3(":/Images/Lamp_on_yellow_3.png");
    QPixmap yellow4(":/Images/Lamp_on_yellow_4.png");
    QPixmap yellow5(":/Images/Lamp_on_yellow_5.png");
    QString status = "On";
    if(color == 0){
        if(brightness <= 20){
            ui->LAMP_label->setPixmap(red1.scaled(300,300,Qt::KeepAspectRatio));
        }else if(brightness > 20 && brightness <= 40){
            ui->LAMP_label->setPixmap(red2.scaled(300,300,Qt::KeepAspectRatio));
        }else if(brightness > 40 && brightness <= 60){
            ui->LAMP_label->setPixmap(red3.scaled(300,300,Qt::KeepAspectRatio));
        }else if(brightness > 60 && brightness <= 80){
            ui->LAMP_label->setPixmap(red4.scaled(300,300,Qt::KeepAspectRatio));
        }else{
            ui->LAMP_label->setPixmap(red5.scaled(300,300,Qt::KeepAspectRatio));
        }
    }else if(color == 1){
        if(brightness <= 20){
            ui->LAMP_label->setPixmap(yellow1.scaled(300,300,Qt::KeepAspectRatio));
        }else if(brightness > 20 && brightness <= 40){
            ui->LAMP_label->setPixmap(yellow2.scaled(300,300,Qt::KeepAspectRatio));
        }else if(brightness > 40 && brightness <= 60){
            ui->LAMP_label->setPixmap(yellow3.scaled(300,300,Qt::KeepAspectRatio));
        }else if(brightness > 60 && brightness <= 80){
            ui->LAMP_label->setPixmap(yellow4.scaled(300,300,Qt::KeepAspectRatio));
        }else{
            ui->LAMP_label->setPixmap(yellow5.scaled(300,300,Qt::KeepAspectRatio));
        }
    }else{
        if(brightness <= 20){
            ui->LAMP_label->setPixmap(blue1.scaled(300,300,Qt::KeepAspectRatio));
        }else if(brightness > 20 && brightness <= 40){
            ui->LAMP_label->setPixmap(blue2.scaled(300,300,Qt::KeepAspectRatio));
        }else if(brightness > 40 && brightness <= 60){
            ui->LAMP_label->setPixmap(blue3.scaled(300,300,Qt::KeepAspectRatio));
        }else if(brightness > 60 && brightness <= 80){
            ui->LAMP_label->setPixmap(blue4.scaled(300,300,Qt::KeepAspectRatio));
        }else{
            ui->LAMP_label->setPixmap(blue5.scaled(300,300,Qt::KeepAspectRatio));
        }
    }
    write_status_bed(filename, line, i, sumline, status, 12);
}

void bed_room::on_Off_LAMP_Btn_clicked()
{
    QString status = "Off";
    qInfo() << "Da tat Den";
    QPixmap bed(":/Images/Lamp_off.png");
    ui->LAMP_label->setPixmap(bed.scaled(300,300,Qt::KeepAspectRatio));
    write_status_bed(filename, line, i, sumline, status, 12);
}

void bed_room::on_PW_LAMP_hS_valueChanged(int value = 0)
{
    if(read_statusFile_bed(filename, line, i, 12) == "On"){
        brightness = value;
        qInfo() << "Cong suat cua Den: " << brightness;
        on_On_LAMP_Btn_clicked();
        QString status = QString::number(value); // chuyen in sang string
        write_status_bed(filename, line, i, sumline, status, 14);
        ui->progressBar->setValue(value+1);
    }else{
        qInfo() << "Den chua duoc bat!!!";
    }
}

void bed_room::on_On_LAMP_red_Btn_clicked()
{
    if(read_statusFile_bed(filename, line, i, 12) == "Off"){
        qInfo() << "Den chua duoc bat!!!";
    }else{
        color = 0;
        on_On_LAMP_Btn_clicked();
        qInfo() << "Da chon Den Red";
    }
}

void bed_room::on_On_LAMP_yellow_Btn_clicked()
{
    if(read_statusFile_bed(filename, line, i, 12) == "Off"){
        qInfo() << "Lamp chua duoc bat!!!";
    }else{
        color = 1;
        on_On_LAMP_Btn_clicked();
        qInfo() << "Da chon Den Yellow";
    }
}

void bed_room::on_On_LAMP_blue_Btn_clicked()
{
    if(read_statusFile_bed(filename, line, i, 12) == "Off"){
        qInfo() << "Den chua duoc bat!!!";
    }else{
        color = 2;
        on_On_LAMP_Btn_clicked();
        qInfo() << "Da chon Den Blue";
    }
}

// *********************************

void bed_room::on_logout_bed_Btn_clicked()
{
    hide();
    main_room *main_room;
    main_room = new class main_room(this);
    main_room->show();
}

void bed_room::on_upgrate_bed_Btn_clicked()
{
    readStatuswhenWrite();
}

void bed_room::readStatuswhenWrite()
{
    // read status from file text
    // read status TV //////////////////////////////
    if(read_statusFile_bed(filename, line, i, 2) == "On"){
        on_On_TV_Btn_clicked();
    }
    else{
        qInfo() << read_statusFile_bed(filename, line, i, 2);
        on_Off_TV_Btn_clicked();
    }
    QString status = read_statusFile_bed(filename, line, i, 4);
    TV = QVariant(status).toInt();
    ui->progressBar_TV->setValue(TV);
    // read status AC ///////////////////////////////
    if(read_statusFile_bed(filename, line, i, 7) == "On"){
        on_On_AC_Btn_clicked();
    }
    else{
        on_Off_AC_Btn_clicked();
    }
    status = read_statusFile_bed(filename, line, i, 9);
    temp = QVariant(status).toInt();
    ui->Temp_label->setText(QString("Temp = %1 °C").arg(temp));
    // read status LAMP //////////////////////////////
    if(read_statusFile_bed(filename, line, i, 12) == "On"){
        on_On_LAMP_Btn_clicked();
    }
    else{
        on_Off_LAMP_Btn_clicked();
    }
    status = read_statusFile_bed(filename, line, i, 14);
    brightness = QVariant(status).toInt();
    on_PW_LAMP_hS_valueChanged(brightness);
    ui->progressBar->setValue(brightness+1);
}


