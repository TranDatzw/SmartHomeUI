#pragma once
#include "main_room.h"
#include "ui_main_room.h"
#include "mainwindow.h"
#include <QPixmap>
#include <QDateTime>
#include <QFile>
MainWindow *mainw;

main_room::main_room(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::main_room)
{
    ui->setupUi(this);
    // timer
    // timer Digital clock
    timer_DLC = new QTimer(this);
    connect(timer_DLC, SIGNAL(timeout()),this, SLOT(Digital_Clock()));
    connect(timer_DLC, SIGNAL(timeout()),this, SLOT(Temp_main()));
    connect(timer_DLC, SIGNAL(timeout()),this, SLOT(Do_am_main()));
    timer_DLC->start(1000);
    /***/
    QPixmap temp(":/Images/temp.png");
    QPixmap doam(":/Images/doam.png");
    ui->label_temp->setPixmap(temp.scaled(100,100,Qt::KeepAspectRatio));
    ui->label_doam->setPixmap(doam.scaled(100,100,Qt::KeepAspectRatio));
    on_on_off_wifi_Btn_clicked();
    on_camera_Btn_clicked();
    on_on_off_key_Btn_clicked();
    setButtonIcon();   
}

main_room::~main_room()
{
    delete ui;
}

// to class **********************

void main_room::on_living_room_Btn_clicked()
{
    hide();
    living_room = new class living_room(this);
    living_room->show();
}

void main_room::on_bed_room_Btn_clicked()
{
    hide();
    bed_room = new class bed_room(this);
    bed_room->show();
}

void main_room::on_kitchen_room_Btn_clicked()
{
    hide();
    kitchen = new class kitchen(this);
    kitchen->show();
}

void main_room::on_logout_main_room_Btn_clicked()
{
    hide();
    mainw = new class MainWindow(this);
    mainw->show();
}

void main_room::on_change_pw_Btn_clicked()
{
    hide();
    change_pw = new class change_password(this);
    change_pw->show();
}

void main_room::on_bath_room_Btn_clicked()
{
    hide();
    bath_room = new class bath_room(this);
    bath_room->show();
}

// *******************************

// *** set icon Button

void main_room::setButtonIcon()
{
    QImage img_living;
    QPixmap pixmap_living;
    QImage img_bed;
    QPixmap pixmap_bed;
    QImage img_bath;
    QPixmap pixmap_bath;
    QImage img_kitchen;
    QPixmap pixmap_kitchen;
    img_living.load(":/Images/Living.png");
    pixmap_living = QPixmap::fromImage(img_living).scaled(40, 40);
    ui->living_room_Btn->setIcon(QIcon(pixmap_living));
    ui->living_room_Btn->setIconSize(QSize(40, 40));

    img_bed.load(":/Images/Bed.png");
    pixmap_bed = QPixmap::fromImage(img_bed).scaled(40, 40);
    ui->bed_room_Btn->setIcon(QIcon(pixmap_bed));
    ui->bed_room_Btn->setIconSize(QSize(40, 40));

    img_bath.load(":/Images/Bath.png");
    pixmap_bath = QPixmap::fromImage(img_bath).scaled(40, 40);
    ui->bath_room_Btn->setIcon(QIcon(pixmap_bath));
    ui->bath_room_Btn->setIconSize(QSize(40, 40));

    img_kitchen.load(":/Images/Kitchen.png");
    pixmap_kitchen = QPixmap::fromImage(img_kitchen).scaled(40, 40);
    ui->kitchen_room_Btn->setIcon(QIcon(pixmap_kitchen));
    ui->kitchen_room_Btn->setIconSize(QSize(40, 40));
}

// *******************************

// Camrera

void main_room::on_camera_Btn_clicked()
{
    camera = !camera;
    QPixmap living(":/Images/living_room.jpg");
    QPixmap garage(":/Images/garage.jpg");
    QPixmap bed(":/Images/bed_room.jpg");
    QPixmap camera_off(":/Images/camera_off.png");
    int w = ui->label_bed->width();
    int h = ui->label_bed->height();
    if(camera==true){
        qInfo() << "Da bat Camera!!!";
        ui->label_bed->setPixmap(bed.scaled(300,300,Qt::KeepAspectRatio));
        ui->label_living->setPixmap(living.scaled(300,300,Qt::KeepAspectRatio));
        ui->label_garage->setPixmap(garage.scaled(300,300,Qt::KeepAspectRatio));
    }else{
        qInfo() << "Da tat Camera!!!";
        ui->label_bed->setPixmap(camera_off.scaled(w,h+200,Qt::KeepAspectRatio));
        ui->label_living->setPixmap(camera_off.scaled(w,h+200,Qt::KeepAspectRatio));
        ui->label_garage->setPixmap(camera_off.scaled(w,h+200,Qt::KeepAspectRatio));
    }
}

// *******************************

// Digital

void main_room::Digital_Clock()
{
    QTime time = QTime::currentTime();
    QString time_text = time.toString("hh : mm : ss");
    if(time.second() % 2 == 0){
        time_text[3] = ' ';
        time_text[8] = ' ';
    }
    ui->label_date_time->setText(time_text);
}

// ******************************

// Wifi

void main_room::on_on_off_wifi_Btn_clicked()
{
    QPixmap wifi_on(":/Images/Wifi_on.png");
    QPixmap wifi_off(":/Images/Wifi_off.png");
    wifi = !wifi;
    if(wifi == true){
        qInfo() << "Wifi on";
        ui->label_wifi->setPixmap(wifi_on.scaled(100,100,Qt::KeepAspectRatio));
    }else{
        qInfo() << "Wifi off";
        ui->label_wifi->setPixmap(wifi_off.scaled(100,100,Qt::KeepAspectRatio));
    }
}

void main_room::on_on_off_key_Btn_clicked()
{
    QPixmap key_on(":/Images/Key_on.png");
    QPixmap key_off(":/Images/Key_off.png");
    key = !key;
    if(key == true){
        qInfo() << "Smart home clocked";
        ui->label_key->setPixmap(key_on.scaled(100,100,Qt::KeepAspectRatio));
    }else{
        qInfo() << "Smart home is not clock!!!";
        ui->label_key->setPixmap(key_off.scaled(100,100,Qt::KeepAspectRatio));
    }
}

// *********************************

// Nhiet do va do am (timer)

void main_room::Temp_main()
{
    QPixmap hot_1(":/Images/hot_2.png");
    QPixmap hot_2(":/Images/hot_5.png");
    QPixmap cool_1(":/Images/cool_2.png");
    QPixmap cool_2(":/Images/cool_5.png");
    QTime time = QTime::currentTime();
     if(time.second() % 10 == 0){
         if(Temp >=0 && Temp < 3){
            Temp += 1;
         }else{
             Temp = 0;
         }
         if(Temp == 0){
            ui->label_temp->setPixmap(hot_2.scaled(100,100,Qt::KeepAspectRatio));
         }else if(Temp == 1){
            ui->label_temp->setPixmap(hot_1.scaled(100,100,Qt::KeepAspectRatio));
         }else if(Temp == 2){
             ui->label_temp->setPixmap(cool_1.scaled(100,100,Qt::KeepAspectRatio));
         }else {
             ui->label_temp->setPixmap(cool_2.scaled(100,300,Qt::KeepAspectRatio));
         }
     }
}

void main_room::Do_am_main()
{
    QPixmap doam_0(":/Images/doam.png");
    QPixmap doam_1(":/Images/doam_1.png");
    QPixmap doam_2(":/Images/doam_2.png");
    QPixmap doam_3(":/Images/doam_3.png");
     QTime time = QTime::currentTime();
     if(time.second() % 10 == 0){
         if(Doam >=0 && Doam < 3){
            Doam += 1;
         }else{
             Doam = 0;
         }

         if(Doam == 0){
            ui->label_doam->setPixmap(doam_0.scaled(100,100,Qt::KeepAspectRatio));
         }else if(Doam == 1){
            ui->label_doam->setPixmap(doam_1.scaled(100,100,Qt::KeepAspectRatio));
         }else if(Doam == 2){
             ui->label_doam->setPixmap(doam_2.scaled(100,100,Qt::KeepAspectRatio));
         }else {
             ui->label_doam->setPixmap(doam_3.scaled(100,300,Qt::KeepAspectRatio));
         }
     }
}

// *********************************

