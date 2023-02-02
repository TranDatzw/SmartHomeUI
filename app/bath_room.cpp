#include "bath_room.h"
#include "ui_bath_room.h"
#include "main_room.h"
#include <QPixmap>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

// File ****************************

int sumLineFile_bath(QString filename, QString line[], int &sumline){
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

QString read_statusFile_bath(QString filename, QString line[], int &i, int location){
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

// **********************************

bath_room::bath_room(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bath_room)
{
    ui->setupUi(this);

    sumline = sumLineFile_bath(filename, line, sumline);
    readStatuswhenWrite();
}

bath_room::~bath_room()
{
    delete ui;
}

bool write_status_bath(QString filename, QString line[], int i, int sumline, QString status, int location){
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        qCritical() << file.errorString();
        return false;
    }
    QTextStream stream(&file);
    for(int j = 0; j < sumline ; j++){
        if(j < location){
            stream << read_statusFile_bath(filename, line, i, j) << Qt::endl;
        }
        else if(j == location){
             stream << status << Qt::endl;
        }
        else{
            stream << read_statusFile_bath(filename, line, i, j) << Qt::endl;
        }
    }
    file.close();
    return true;
}

void bath_room::on_logout_bath_clicked()
{
    hide();
    main_room *main_room;
    main_room = new class main_room(this);
    main_room->show();
}

// Music Speaker ****************************************

void bath_room::on_MS_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void bath_room::on_On_MS_Btn_clicked()
{
    QPixmap bray(":/Images/xindungnhacmay.jpg");
    QPixmap noo(":/Images/yeumotnguoisaobuondenthe.jpg");
    QPixmap h_lam(":/Images/chinhminh.jpg");
    QPixmap k_dang(":/Images/henyeu.jpg");
    QPixmap zingmp3(":/Images/zingmp3.png");
    QString status = "On";
    if(KenhTV == 0){
       qInfo() << "Xin dung nhac may";
       ui->MS_label->setPixmap(bray.scaled(300,300,Qt::KeepAspectRatio));
    }else if(KenhTV == 1){
        qInfo() << "Yeu mot nguoi sao buon den the";
        ui->MS_label->setPixmap(noo.scaled(300,300,Qt::KeepAspectRatio));
    }else if(KenhTV == 2){
        qInfo() << "Chinh minh";
        ui->MS_label->setPixmap(h_lam.scaled(300,300,Qt::KeepAspectRatio));
    }else if(KenhTV == 3){
        qInfo() << "Hen yeu";
        ui->MS_label->setPixmap(k_dang.scaled(300,300,Qt::KeepAspectRatio));
    }else{
        qInfo() << "Music Speaker da bat";
        ui->MS_label->setPixmap(zingmp3.scaled(300,300,Qt::KeepAspectRatio));
    }
    write_status_bath(filename, line, i, sumline, status, 2);
}

void bath_room::on_Off_MS_Btn_clicked()
{
    QString status = "Off";
    qInfo() << "Da tat Music Speaker!!!";
    QPixmap bath(":/Images/music_speaker.png");
    ui->MS_label->setPixmap(bath.scaled(300,300,Qt::KeepAspectRatio));
    write_status_bath(filename, line, i, sumline, status, 2);
}

void bath_room::on_up_volume_Btn_clicked()
{
    if(read_statusFile_bath(filename, line, i, 2) == "On"){
        TV++;
        qInfo() << "Volume Music Speaker: " << TV;
    }
    else{
        qInfo() << "Music Speaker chua duoc bat!!!";
    }
    QString status = QString::number(TV);
    write_status_bath(filename, line, i, sumline, status, 4);
    ui->progressBar_MS->setValue(TV);
}

void bath_room::on_down_volume_Btn_clicked()
{
    ui->progressBar_MS->setValue(TV);
    if(read_statusFile_bath(filename, line, i, 2) == "On"){
        TV--;
        qInfo() << "Volume Music Speaker: " << TV;
    }
    else{
        qInfo() << "Music Speaker chua duoc bat!!!";
    }
    QString status = QString::number(TV);
    write_status_bath(filename, line, i, sumline, status, 4);
    ui->progressBar_MS->setValue(TV);
}

void bath_room::on_previus_MS_Btn_clicked()
{
    if(read_statusFile_bath(filename, line, i, 2) == "On"){
        if(KenhTV > 0 && KenhTV < 4)
           KenhTV--;
        else{
           KenhTV = 3;
        }
        on_On_MS_Btn_clicked();
    }else{
        qInfo() << "Music Speaker chua duoc bat";
    }
}

void bath_room::on_next_volume_Btn_clicked()
{
    if(read_statusFile_bath(filename, line, i, 2) == "On"){
        if(KenhTV >= 0 && KenhTV < 3)
           KenhTV++;
        else{
           KenhTV = 0;
        }
        on_On_MS_Btn_clicked();
    }
    else{
        qInfo() << "Music Speaker chua duoc bat";
    }
}

// ****************************************

// May nuoc nong lanh

void bath_room::on_WM_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void bath_room::on_On_WM_Btn_clicked()
{
    if(read_statusFile_bath(filename, line, i, 7) == "Off"){
        qInfo() << "May nuoc nong da duoc bat";
    }
    QString status = "On";
    QPixmap hot1(":/Images/hot_1.png");
    QPixmap hot2(":/Images/hot_2.png");
    QPixmap hot3(":/Images/hot_3.png");
    QPixmap hot4(":/Images/hot_4.png");
    QPixmap hot5(":/Images/hot_5.png");
    QPixmap cool1(":/Images/cool_1.png");
    QPixmap cool2(":/Images/cool_2.png");
    QPixmap cool3(":/Images/cool_3.png");
    QPixmap cool4(":/Images/cool_4.png");
    QPixmap cool5(":/Images/cool_5.png");
    QPixmap bath(":/Images/water_machine.png");
    // -20 -15 -10 -5 0 5 10 15 20 25 30 35 40
    if(temp >=-20 && temp < -15){
        ui->label_temp_img->setPixmap(cool5.scaled(100,100,Qt::KeepAspectRatio));
    }else if(temp >=-15 && temp < -10){
        ui->label_temp_img->setPixmap(cool4.scaled(100,100,Qt::KeepAspectRatio));
    }else if(temp >=-10 && temp < -5){
        ui->label_temp_img->setPixmap(cool3.scaled(100,100,Qt::KeepAspectRatio));
    }else if(temp >=-5 && temp < 0){
        ui->label_temp_img->setPixmap(cool2.scaled(100,100,Qt::KeepAspectRatio));
    }else if(temp >=0 && temp < 5){
        ui->label_temp_img->setPixmap(cool1.scaled(100,100,Qt::KeepAspectRatio));
    }else if(temp >= 5 && temp < 10){
        ui->label_temp_img->setPixmap(hot1.scaled(100,100,Qt::KeepAspectRatio));
    }else if(temp >=10 && temp < 15){
        ui->label_temp_img->setPixmap(hot2.scaled(100,100,Qt::KeepAspectRatio));
    }else if(temp >=15 && temp < 20){
        ui->label_temp_img->setPixmap(hot3.scaled(100,100,Qt::KeepAspectRatio));
    }else if(temp >=20 && temp < 25){
        ui->label_temp_img->setPixmap(hot4.scaled(100,100,Qt::KeepAspectRatio));
    }else if(temp >=30 && temp < 35){
        ui->label_temp_img->setPixmap(hot5.scaled(100,100,Qt::KeepAspectRatio));
    }
    ui->WM_label->setPixmap(bath.scaled(300,300,Qt::KeepAspectRatio));
    write_status_bath(filename, line, i, sumline, status, 7);
}

void bath_room::on_Off_WM_Btn_clicked()
{
    QString status = "Off";
    qInfo() << "Da tat May nuoc nong!!!";
    QPixmap temp(":/Images/temp.png");
    ui->label_temp_img->setPixmap(temp.scaled(100,100,Qt::KeepAspectRatio));
    ui->WM_label->clear();
    write_status_bath(filename, line, i, sumline, status, 7);
}

void bath_room::on_up_WM_Btn_clicked()
{
    if(read_statusFile_bath(filename, line, i, 7) == "Off"){
        qInfo() << "May nuoc nong chua bat!!!";
    }
    else{
        if(temp < 50){
            temp++;
            qInfo() << "Nhiet do nuoc: " << temp;
        }
    }
    on_On_WM_Btn_clicked();
    QString status = QString::number(temp); // chuyen in sang string
    write_status_bath(filename, line, i, sumline, status, 9);
    ui->Temp_label->setText(QString("Temp = %1 °C").arg(temp));
}

void bath_room::on_down_WM_Btn_clicked()
{
    if(read_statusFile_bath(filename, line, i, 7) == "Off"){
        temp = 0;
    }
    else{
        if(temp > -30){
            qInfo() << "Nhiet do nuoc: " << temp;
            temp--;
        }
    }
    on_On_WM_Btn_clicked();
    QString status = QString::number(temp); // chuyen in sang string
    write_status_bath(filename, line, i, sumline, status, 9);
    ui->Temp_label->setText(QString("Temp = %1 °C").arg(temp));
}

// ***************************************

// Lamp

void bath_room::on_LAMP_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void bath_room::on_On_LAMP_Btn_clicked()
{
    if(read_statusFile_bath(filename, line, i, 12) == "Off"){
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
    write_status_bath(filename, line, i, sumline, status, 12);
}

void bath_room::on_Off_LAMP_Btn_clicked()
{
    QString status = "Off";
    qInfo() << "Da tat Den";
    QPixmap bath(":/Images/Lamp_off.png");
    ui->LAMP_label->setPixmap(bath.scaled(300,300,Qt::KeepAspectRatio));
    write_status_bath(filename, line, i, sumline, status, 12);
}

void bath_room::on_PW_LAMP_hS_valueChanged(int value = 0)
{
    if(read_statusFile_bath(filename, line, i, 12) == "On"){
        brightness = value;
        qInfo() << "Cong suat cua Den: " << brightness;
        on_On_LAMP_Btn_clicked();
        QString status = QString::number(value); // chuyen in sang string
        write_status_bath(filename, line, i, sumline, status, 14);
        ui->progressBar->setValue(value+1);
    }else{
        qInfo() << "Den chua duoc bat!!!";
    }
}

void bath_room::on_On_LAMP_red_Btn_clicked()
{
    if(read_statusFile_bath(filename, line, i, 12) == "Off"){
        qInfo() << "Den chua duoc bat!!!";
    }else{
        color = 0;
        on_On_LAMP_Btn_clicked();
        qInfo() << "Da chon Den Red";
    }
}

void bath_room::on_On_LAMP_yellow_Btn_clicked()
{
    if(read_statusFile_bath(filename, line, i, 12) == "Off"){
        qInfo() << "Lamp chua duoc bat!!!";
    }else{
        color = 1;
        on_On_LAMP_Btn_clicked();
        qInfo() << "Da chon Den Yellow";
    }
}

void bath_room::on_On_LAMP_blue_Btn_clicked()
{
    if(read_statusFile_bath(filename, line, i, 12) == "Off"){
        qInfo() << "Den chua duoc bat!!!";
    }else{
        color = 2;
        on_On_LAMP_Btn_clicked();
        qInfo() << "Da chon Den Blue";
    }
}

// *********************************


void bath_room::on_upgrate_bath_Btn_clicked()
{
    readStatuswhenWrite();
}

void bath_room::readStatuswhenWrite()
{
    // read status from file text
    // read status MS //////////////////////////////
    if(read_statusFile_bath(filename, line, i, 2) == "On"){
        on_On_MS_Btn_clicked();
    }
    else{
        on_Off_MS_Btn_clicked();
    }
    QString status = read_statusFile_bath(filename, line, i, 4);
    TV = QVariant(status).toInt();
    ui->progressBar_MS->setValue(TV);
    // read status WM ///////////////////////////////
    if(read_statusFile_bath(filename, line, i, 7) == "On"){
        on_On_WM_Btn_clicked();
    }
    else{
        on_Off_WM_Btn_clicked();
    }
    status = read_statusFile_bath(filename, line, i, 9);
    temp = QVariant(status).toInt();
    ui->Temp_label->setText(QString("Temp = %1 °C").arg(temp));
    // read status LAMP //////////////////////////////
    if(read_statusFile_bath(filename, line, i, 12) == "On"){
        on_On_LAMP_Btn_clicked();
    }
    else{
        on_Off_LAMP_Btn_clicked();
    }
    status = read_statusFile_bath(filename, line, i, 14);
    brightness = QVariant(status).toInt();
    on_PW_LAMP_hS_valueChanged(brightness);
    ui->progressBar->setValue(brightness+1);
}

void bath_room::on_logout_bath_Btn_clicked()
{
    hide();
    main_room *main_room;
    main_room = new class main_room(this);
    main_room->show();
}

