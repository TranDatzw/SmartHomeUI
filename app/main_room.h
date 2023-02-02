#pragma once
#ifndef MAIN_ROOM_H
#define MAIN_ROOM_H

#include <QDialog>
#include "living_room.h"
#include "bed_room.h"
#include "kitchen.h"
#include "bath_room.h"
#include "change_password.h"
#include <QTimer>

namespace Ui {
class main_room;
}

class main_room : public QDialog
{
    Q_OBJECT

public:
    explicit main_room(QWidget *parent = nullptr);
    ~main_room();

private slots:
    void on_living_room_Btn_clicked();

    void on_bed_room_Btn_clicked();

    void on_kitchen_room_Btn_clicked();

    void on_logout_main_room_Btn_clicked();

    void on_change_pw_Btn_clicked();

    void on_bath_room_Btn_clicked();

    void on_camera_Btn_clicked();

    void Digital_Clock();

    void Temp_main();

    void Do_am_main();

    void on_on_off_wifi_Btn_clicked();

    void on_on_off_key_Btn_clicked();

private:
    Ui::main_room *ui;
    living_room *living_room;
    bed_room *bed_room;
    kitchen *kitchen;
    bath_room *bath_room;
    change_password *change_pw;
    void setButtonIcon();
    bool camera = false;
    QTimer *timer_DLC;
    int Temp = 0;
    int Doam = 0;
    bool wifi = false;
    bool key = false;
};

#endif // MAIN_ROOM_H
