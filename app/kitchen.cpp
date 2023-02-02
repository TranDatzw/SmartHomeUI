#include "kitchen.h"
#include "ui_kitchen.h"
#include "main_room.h"
#include <QPixmap>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

// * Ham cho file ***************************************

int sumLineFile_kitchen(QString filename, QString line[], int &sumline){
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

QString read_statusFile_kitchen(QString filename, QString line[], int &i, int location){
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

bool write_status_kitchen(QString filename, QString line[], int i, int sumline, QString status, int location){
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        qCritical() << file.errorString();
        return false;
    }

    QTextStream stream(&file);
    for(int j = 0; j < sumline ; j++){
        if(j < location){
            stream << read_statusFile_kitchen(filename, line, i, j) << Qt::endl;
        }
        else if(j == location){
             stream << status << Qt::endl;
        }
        else{
            stream << read_statusFile_kitchen(filename, line, i, j) << Qt::endl;
        }
    }
    file.close();
    return true;
}

// ******************************************************

kitchen::kitchen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::kitchen)
{
    ui->setupUi(this);

    sumline = sumLineFile_kitchen(filename, line, sumline);
    readStatuswhenWrite();
}

kitchen::~kitchen()
{
    delete ui;
}


// * ham khac **************************************

void kitchen::on_logout_kitchen_Btn_clicked()
{
    hide();
    main_room *main_room;
    main_room = new class main_room(this);
    main_room->show();
}

void kitchen::on_upgrate_kitchen_Btn_clicked()
{
    readStatuswhenWrite();
}

void kitchen::readStatuswhenWrite()
{
    // read status from file text
    // read status TV //////////////////////////////
    if(read_statusFile_kitchen(filename, line, i, 2) == "On"){
        on_On_Fri_Btn_clicked();
    }
    else{
        on_Off_Fri_Btn_clicked();
    }
    // read status AC ///////////////////////////////
    if(read_statusFile_kitchen(filename, line, i, 5) == "On"){
        on_On_GAS_Btn_clicked();
    }
    else{
        on_Off_GAS_Btn_clicked();
    }
    QString status = read_statusFile_kitchen(filename, line, i, 7);
    level = QVariant(status).toInt();
    ui->Temp_label->setText(QString("Level = %1").arg(level));
    // read status LAMP //////////////////////////////
    if(read_statusFile_kitchen(filename, line, i, 10) == "On"){
        on_On_LAMP_Btn_clicked();
    }
    else{
        on_Off_LAMP_Btn_clicked();
    }
    status = read_statusFile_kitchen(filename, line, i, 12);
    brightness = QVariant(status).toInt();
    on_PW_LAMP_hS_valueChanged(brightness);
    ui->progressBar->setValue(brightness+1);
}

// Tu lanh *****************************************

void kitchen::on_Fri_Btn_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}

void kitchen::on_On_Fri_Btn_clicked()
{
    QString status = "On";
    qInfo() << "Mo tu lanh:" ;
    QPixmap vtvcab(":/Images/fridge_on.png");
    ui->Fri_label->setPixmap(vtvcab.scaled(300,300,Qt::KeepAspectRatio));
    write_status_kitchen(filename, line, i, sumline, status, 2);
}

void kitchen::on_Off_Fri_Btn_clicked()
{
    QString status = "Off";
    qInfo() << "Dong tu lanh:" ;
    QPixmap vtvcab(":/Images/fridge_off.png");
    ui->Fri_label->setPixmap(vtvcab.scaled(300,300,Qt::KeepAspectRatio));
    write_status_kitchen(filename, line, i, sumline, status, 2);
}

// ************************************************

// GAS *******************************************

void kitchen::on_GAS_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void kitchen::on_On_GAS_Btn_clicked()
{
    QPixmap khi_gas(":/Images/khi_gas.png");
    QPixmap khi_gas1(":/Images/khi_gas_1.png");
    QPixmap khi_gas2(":/Images/khi_gas_2.png");
    QPixmap khi_gas3(":/Images/khi_gas_3.png");
    QString status = "On";
    if(level == 0){
       qInfo() << "Binh gas dang bat voi level: "<< level;
       ui->label_khi_gas_img->setPixmap(khi_gas.scaled(100,100,Qt::KeepAspectRatio));
    }else if(level == 1){
        qInfo() << "Binh gas dang bat voi level: "<< level;
        ui->label_khi_gas_img->setPixmap(khi_gas1.scaled(100,100,Qt::KeepAspectRatio));
    }else if(level == 2){
        qInfo() << "Binh gas dang bat voi level: "<< level;
        ui->label_khi_gas_img->setPixmap(khi_gas2.scaled(100,100,Qt::KeepAspectRatio));
    }else{
        qInfo() << "Binh gas dang bat";
        ui->label_khi_gas_img->setPixmap(khi_gas3.scaled(100,100,Qt::KeepAspectRatio));
    }
    write_status_kitchen(filename, line, i, sumline, status, 5);
    QPixmap gas_on(":/Images/gas_on.png");
    ui->GAS_label->setPixmap(gas_on.scaled(300,300,Qt::KeepAspectRatio));
}

void kitchen::on_Off_GAS_Btn_clicked()
{
    QString status = "Off";
    qInfo() << "Da tat binh gas";
    QPixmap gas_off(":/Images/gas_off.png");
    QPixmap khi_gas(":/Images/khi_gas.png");
    level = 0;
    ui->label_khi_gas_img->setPixmap(khi_gas.scaled(100,100,Qt::KeepAspectRatio));
    ui->GAS_label->setPixmap(gas_off.scaled(300,300,Qt::KeepAspectRatio));
    ui->Temp_label->setText(QString("Level = %1 ").arg(level));
    write_status_kitchen(filename, line, i, sumline, status, 5);
}

void kitchen::on_up_GAS_Btn_clicked()
{
    QPixmap khi_gas(":/Images/khi_gas.png");
    if(read_statusFile_kitchen(filename, line, i, 5) == "On"){
        if(level < 3){
            level++;
            qInfo() << "Binh gas dang bat voi level: "<< level;
        }
        on_On_GAS_Btn_clicked();
    }
    else{
        level = 0;
        qInfo() << "Binh gas dang tat!!!";
        ui->label_khi_gas_img->setPixmap(khi_gas.scaled(100,100,Qt::KeepAspectRatio));
    }
    QString status = QString::number(level); // chuyen in sang string
    write_status_kitchen(filename, line, i, sumline, status, 7);
    ui->Temp_label->setText(QString("Level = %1 ").arg(level));
}

void kitchen::on_down_GAS_Btn_clicked()
{
    QPixmap khi_gas(":/Images/khi_gas.png");
    if(read_statusFile_kitchen(filename, line, i, 5) == "On"){
        if(level > 0){
            level--;
            qInfo() << "Binh gas dang bat voi level: "<< level;
        }
        on_On_GAS_Btn_clicked();
    }else{
        level =0;
        qInfo() << "Binh gas dang tat!!!";
        ui->label_khi_gas_img->setPixmap(khi_gas.scaled(100,100,Qt::KeepAspectRatio));
    }
    QString status = QString::number(level); // chuyen in sang string
    write_status_kitchen(filename, line, i, sumline, status, 7);
    ui->Temp_label->setText(QString("Level = %1 ").arg(level));
}

// **********************************************// **********************************************

// Lamp

void kitchen::on_LAMP_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void kitchen::on_On_LAMP_Btn_clicked()
{
    if(read_statusFile_kitchen(filename, line, i, 10) == "Off"){
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
    write_status_kitchen(filename, line, i, sumline, status, 10);
}

void kitchen::on_Off_LAMP_Btn_clicked()
{
    QString status = "Off";
    qInfo() << "Da tat Den";
    QPixmap kitchen(":/Images/Lamp_off.png");
    ui->LAMP_label->setPixmap(kitchen.scaled(300,300,Qt::KeepAspectRatio));
    write_status_kitchen(filename, line, i, sumline, status, 10);
}

void kitchen::on_PW_LAMP_hS_valueChanged(int value = 0)
{
    if(read_statusFile_kitchen(filename, line, i, 10) == "On"){
        brightness = value;
        qInfo() << "Cong suat cua Den: " << brightness;
        on_On_LAMP_Btn_clicked();
        QString status = QString::number(value); // chuyen in sang string
        write_status_kitchen(filename, line, i, sumline, status, 12);
        ui->progressBar->setValue(value+1);
    }else{
        qInfo() << "Den chua duoc bat!!!";
    }
}

void kitchen::on_On_LAMP_red_Btn_clicked()
{
    if(read_statusFile_kitchen(filename, line, i, 10) == "Off"){
        qInfo() << "Den chua duoc bat!!!";
    }else{
        color = 0;
        on_On_LAMP_Btn_clicked();
        qInfo() << "Da chon Den Red";
    }
}

void kitchen::on_On_LAMP_yellow_Btn_clicked()
{
    if(read_statusFile_kitchen(filename, line, i, 10) == "Off"){
        qInfo() << "Lamp chua duoc bat!!!";
    }else{
        color = 1;
        on_On_LAMP_Btn_clicked();
        qInfo() << "Da chon Den Yellow";
    }
}

void kitchen::on_On_LAMP_blue_Btn_clicked()
{
    if(read_statusFile_kitchen(filename, line, i, 10) == "Off"){
        qInfo() << "Den chua duoc bat!!!";
    }else{
        color = 2;
        on_On_LAMP_Btn_clicked();
        qInfo() << "Da chon Den Blue";
    }
}

// *********************************



