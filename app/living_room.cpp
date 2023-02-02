#include "living_room.h"
#include "ui_living_room.h"
#include"main_room.h"
#include <QPixmap>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
/// *************************

#include <Windows.h>
#include <fstream>
#include <string>
#include <iostream>
#include <conio.h>


using namespace std;
int henri23;
DWORD dwRes;
HANDLE hComm;
DWORD dwRead;
BOOL fWaitingOnRead = FALSE;
OVERLAPPED osReader = { 0 };
char* lpBuf[10];
BOOL henrihenri = TRUE;
int flag=0;
BOOL WriteABuffer(char* lpBuf, DWORD dwToWrite)   // A good working function
{
    OVERLAPPED osWrite = { 0 };
    DWORD dwWritten;
    DWORD dwRes;
    BOOL fRes;

    // Create this write operation's OVERLAPPED structure's hEvent.
    osWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (osWrite.hEvent == NULL)
        // error creating overlapped event handle
        return FALSE;

    // Issue write.
    if (!WriteFile(hComm, lpBuf, dwToWrite, &dwWritten, &osWrite)) {
        if (GetLastError() != ERROR_IO_PENDING) {
            // WriteFile failed, but isn't delayed. Report error and abort.
            fRes = FALSE;
        }
        else
            // Write is pending.
            dwRes = WaitForSingleObject(osWrite.hEvent, INFINITE);
        switch (dwRes)
        {
            // OVERLAPPED structure's event has been signaled.
        case WAIT_OBJECT_0:
            if (!GetOverlappedResult(hComm, &osWrite, &dwWritten, FALSE))
                fRes = FALSE;
            else
                // Write operation completed successfully.
                fRes = TRUE;
            break;

        default:
            // An error has occurred in WaitForSingleObject.
            // This usually indicates a problem with the
            // OVERLAPPED structure's event handle.
            fRes = FALSE;
            break;
        }
    }

    else
        // WriteFile completed immediately.
        fRes = TRUE;

    //	CloseHandle(osWrite.hEvent);   // close the port
    return fRes;
}


void Comport5()
{
    hComm = CreateFile(L"\\\\.\\COM6",   // com5 is ready to communicate ==> open the port
        GENERIC_READ | GENERIC_WRITE,
        0,
        0,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        0);
    std::cout << hComm << endl;
    if (hComm == INVALID_HANDLE_VALUE)
    {
        //std::cout << "ER!" << endl;// error opening port; abort
        //std::cout << GetLastError();
        if (GetLastError() == 2)
        {
            std::cout << "Port 5 is not available!" << endl;

        }
        if (GetLastError() == 5)
        {
            std::cout << "Port 5 is already taken!" << endl;

        }

    }
    else
    {
        flag=1;
        std::cout << flag;
        std::cout << "COM5 is available." << endl;  // And reday to use (TX/RX)
        return;
    }

}

void WriteComport5()
{
    string henri7;
    string line;
    string kq[16];
    string T, M, L;
    int
        TV, ML, LP;
    int i = 0;
    ifstream myfile("D:/Study/N04_HK1/C++/Qt/app/filetext/living.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            kq[i] = line;
            i = i + 1;
        }
        myfile.close();
    }

    if (kq[2] == "On") {

        TV = stoi(kq[4]) + 128;


    }
    else {
        TV = 50;
    }
    if (kq[7] == "On") {
        ML = stoi(kq[9]) + 128;


    }
    else {
        ML = 50;
    }
    if (kq[12] == "On") {
        LP = stoi(kq[14]) + 128;


    }
    else {
        LP = 50;
    }
    T = TV;
    M = ML;
    L = LP;
    henri7 = T + M + L;
    // to proceed it to the next step and read the received character in a real time basis!

  // get the charcter from the user without hitting the Enter
    std::cout << henri7;
    const char* c = henri7.c_str(); // string 2 char *
    WriteABuffer((char*)c, 3);
    std::cout << henri7;



}

int writehardware()
{

    WriteComport5();

 // Jump back and repeat again!

    return 0;


}



///*****************************************8


// * sumLineFile && redstatusFile

int sumLineFile(QString filename, QString line[], int &sumline){
    QFile file(filename);
    sumline = 0;
    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << file.errorString();
        return 0;
    }
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        line[sumline] = stream.readLine();
//        qInfo() << line[i];
        sumline++;
    }
//    qInfo() << sumline;
    file.close();
    return sumline;
}

QString read_statusFile(QString filename, QString line[], int &i, int location){
    QFile file(filename);
    i = 0;
    if(!file.open(QIODevice::ReadOnly)){
        qCritical() << file.errorString();
        return 0;
    }
    QTextStream stream(&file);
    while (!stream.atEnd()) {
        line[i] = stream.readLine(); // doc 1 dong`
//        qInfo() << line[i];
        i++;
    }
//    qInfo() << i;
    file.close();
    return line[location];
}

// ************************************
living_room::living_room(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::living_room)
{
    ui->setupUi(this);

    sumline = sumLineFile(filename, line, sumline);
    readStatuswhenWrite();
}

living_room::~living_room()
{
    delete ui;
}

// write status ***************************

bool write_status(QString filename, QString line[], int i, int sumline, QString status, int location){
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly)){
        qCritical() << file.errorString();
        return false;
    }
    QTextStream stream(&file);
    for(int j = 0; j < sumline ; j++){
        if(j < location){
            stream << read_statusFile(filename, line, i, j) << Qt::endl;
//            qInfo() << "RW" << j << read_statusFile(filename, line, i, j) << Qt::endl;
        }
        else if(j == location){
             stream << status << Qt::endl;
//             qInfo() << status << Qt::endl;
        }
        else{
            stream << read_statusFile(filename, line, i, j) << Qt::endl;
//            qInfo() << "RWtt" << j << read_statusFile(filename, line, i, j) << Qt::endl;
        }
    }

    file.close();
    if (flag!=1){Comport5(); }// hen them}
    std::cout << "tao toi day rooi";
    writehardware();// hen thems
    return true;
}

// ***************************************

// TV *******************************************************************

void living_room::on_TV_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void living_room::on_On_TV_Btn_clicked()
{
    QPixmap vtvcab(":/Images/TV_on_vtvcab.png");
    QPixmap K(":/Images/TV_on_K.png");
    QPixmap htv(":/Images/TV_on_htv.png");
    QPixmap sctv(":/Images/TV_on_sctv.png");
    QString status = "On";
    if(KenhTV == 0){
       qInfo() << "TV dang bat VTVCab";
       ui->TV_label->setPixmap(vtvcab.scaled(300,300,Qt::KeepAspectRatio));
    }else if(KenhTV == 1){
       qInfo() << "TV dang bat K+";
       ui->TV_label->setPixmap(K.scaled(300,300,Qt::KeepAspectRatio));
    }else if(KenhTV == 2){
       qInfo() << "TV dang bat SCTV";
       ui->TV_label->setPixmap(sctv.scaled(300,300,Qt::KeepAspectRatio));
    }else{
       qInfo() << "TV dang bat HTV";
       ui->TV_label->setPixmap(htv.scaled(300,300,Qt::KeepAspectRatio));
    }
    write_status(filename, line, i, sumline, status, 2);
//    qInfo() << read_statusFile(filename, line, i, 2);
}

void living_room::on_Off_TV_Btn_clicked()
{
    QString status = "Off";
    QPixmap living(":/Images/TV_off.png");
    qInfo() << "TV da tat!!!";
    ui->TV_label->setPixmap(living.scaled(300,300,Qt::KeepAspectRatio));
    write_status(filename, line, i, sumline, status, 2);
}

void living_room::on_up_volume_Btn_clicked()
{
    if(read_statusFile(filename, line, i, 2) == "On"){
        TV++;
        qInfo() << "Volume cua TV: " << TV;
    }
    else{
        qInfo() << "TV chua duoc bat!!!";
    }

    QString status = QString::number(TV);
    write_status(filename, line, i, sumline, status, 4);
    ui->progressBar_TV->setValue(TV+1);
}

void living_room::on_down_volume_Btn_clicked()
{
    ui->progressBar_TV->setValue(TV);
    if(read_statusFile(filename, line, i, 2) == "On"){
        TV--;
        qInfo() << "Volume cua TV: " << TV;
    }
    else{
        qInfo() << "TV chua duoc bat!!!";
    }
    QString status = QString::number(TV);
    write_status(filename, line, i, sumline, status, 4);
    ui->progressBar_TV->setValue(TV+1);
}

void living_room::on_previus_TV_Btn_clicked()
{
    if(read_statusFile(filename, line, i, 2) == "On"){
        if(KenhTV > 0 && KenhTV < 4)
           KenhTV--;
        else{
           KenhTV = 3;
        }
//        qInfo() << KenhTV;
        on_On_TV_Btn_clicked();
    }else{
        qInfo() << "TV chua duoc bat";
    }
}

void living_room::on_next_TV_Btn_clicked()
{
    if(read_statusFile(filename, line, i, 2) == "On"){
        if(KenhTV >= 0 && KenhTV < 3)
           KenhTV++;
        else{
           KenhTV = 0;
        }
//        qInfo() << KenhTV;
        on_On_TV_Btn_clicked();
    }
    else{
        qInfo() << "TV chua duoc bat";
    }
}

//**********************************************************************

// May lanh ************************************************************

void living_room::on_AC_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void living_room::on_On_AC_Btn_clicked()
{    
    QString status = "On";
    QPixmap living(":/Images/AC_on.png");
    if(read_statusFile(filename, line, i, 7) == "Off"){
       qInfo() << "May lanh dang bat";
    }
    ui->AC_label->setPixmap(living.scaled(300,300,Qt::KeepAspectRatio));
    write_status(filename, line, i, sumline, status, 7);
}

void living_room::on_Off_AC_Btn_clicked()
{
    QString status = "Off";
    QPixmap living(":/Images/AC_off.png");
    if(read_statusFile(filename, line, i, 7) == "On"){
       qInfo() << "Da tat May lanh";
    }
    ui->AC_label->setPixmap(living.scaled(300,300,Qt::KeepAspectRatio));
    write_status(filename, line, i, sumline, status, 7);
}

void living_room::on_up_AC_Btn_clicked()
{
    if(read_statusFile(filename, line, i, 7) == "On"){
        if (temp < 30){
            temp++;
            qInfo() << "Nhiet do may lanh: " << temp;
        }
    }
    else{
        qInfo() << "May lanh chua duoc bat";
    }
    QString status = QString::number(temp); // chuyen in sang string
    write_status(filename, line, i, sumline, status, 9);
    ui->Temp_label->setText(QString("Temp = %1 °C").arg(temp));
}

void living_room::on_down_AC_Btn_clicked()
{
    if(read_statusFile(filename, line, i, 7) == "On"){
        if (temp > -20){
            temp--;
            qInfo() << "Nhiet do may lanh: " << temp;
        }
    }
    else{
        qInfo() << "May lanh chua duoc bat";
    }
    QString status = QString::number(temp); // chuyen in sang string
    write_status(filename, line, i, sumline, status, 9);
    ui->Temp_label->setText(QString("Temp = %1 °C").arg(temp));
}

// ************************************************************************

void living_room::on_LAMP_Btn_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void living_room::on_On_LAMP_Btn_clicked()
{
    if(read_statusFile(filename, line, i, 12) == "Off"){
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
    write_status(filename, line, i, sumline, status, 12);
    write_status(filename, line, i, sumline, status, 12);
}

void living_room::on_Off_LAMP_Btn_clicked()
{
    QString status = "Off";
    qInfo() << "Da tat Den";
    QPixmap living(":/Images/Lamp_off.png");
    ui->LAMP_label->setPixmap(living.scaled(300,300,Qt::KeepAspectRatio));
    write_status(filename, line, i, sumline, status, 12);
    write_status(filename, line, i, sumline, status, 12);
}

void living_room::on_PW_LAMP_hS_valueChanged(int value = 0)
{
    if(read_statusFile(filename, line, i, 12) == "On"){
        brightness = value;
        qInfo() << "Cong suat cua Den: " << brightness;
        on_On_LAMP_Btn_clicked();
        QString status = QString::number(value); // chuyen in sang string
        write_status(filename, line, i, sumline, status, 14);
        ui->progressBar->setValue(value);
    }else{
        qInfo() << "Den chua duoc bat!!!";
    }
}

void living_room::on_On_LAMP_red_Btn_clicked()
{
    if(read_statusFile(filename, line, i, 12) == "Off"){
        qInfo() << "Den chua duoc bat!!!";
    }else{
        color = 0;
        on_On_LAMP_Btn_clicked();
        qInfo() << "Da chon Den Red";
    }
}

void living_room::on_On_LAMP_yellow_Btn_clicked()
{
    if(read_statusFile(filename, line, i, 12) == "Off"){
        qInfo() << "Lamp chua duoc bat!!!";
    }else{
        color = 1;
        on_On_LAMP_Btn_clicked();
        qInfo() << "Da chon Den Yellow";
    }
}

void living_room::on_On_LAMP_blue_Btn_clicked()
{
    if(read_statusFile(filename, line, i, 12) == "Off"){
        qInfo() << "Den chua duoc bat!!!";
    }else{
        color = 2;
        on_On_LAMP_Btn_clicked();
        qInfo() << "Da chon Den Blue";
    }
}

// ****************************************************************

void living_room::on_logout_living_Btn_clicked()
{
    hide();
    main_room *main_room;
    main_room = new class main_room(this);
    main_room->show();
}

void living_room::on_upgrate_living_Btn_clicked()
{
    readStatuswhenWrite();
}

void living_room::readStatuswhenWrite()
{
    // read status from file text
    // read status TV //////////////////////////////
    if(read_statusFile(filename, line, i, 2) == "On"){
        on_On_TV_Btn_clicked();
    }
    else{
        on_Off_TV_Btn_clicked();
    }
    QString status = read_statusFile(filename, line, i, 4);
    TV = QVariant(status).toInt();
    ui->progressBar_TV->setValue(TV+1);
    // read status AC ///////////////////////////////
    if(read_statusFile(filename, line, i, 7) == "On"){
        on_On_AC_Btn_clicked();
    }
    else{
        on_Off_AC_Btn_clicked();
    }
    status = read_statusFile(filename, line, i, 9);
    temp = QVariant(status).toInt();
    ui->Temp_label->setText(QString("Temp = %1 °C").arg(temp));
    // read status LAMP //////////////////////////////
    if(read_statusFile(filename, line, i, 12) == "On"){
        on_On_LAMP_Btn_clicked();
    }
    else{
        on_Off_LAMP_Btn_clicked();
    }
    status = read_statusFile(filename, line, i, 14);
    brightness = QVariant(status).toInt();
    on_PW_LAMP_hS_valueChanged(brightness);
    ui->progressBar->setValue(brightness+1);
}







