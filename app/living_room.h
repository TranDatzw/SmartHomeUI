#ifndef LIVING_ROOM_H
#define LIVING_ROOM_H

#include <QDialog>
#include <QPixmap>

namespace Ui {
class living_room;
}

class living_room : public QDialog
{
    Q_OBJECT

public:
    explicit living_room(QWidget *parent = nullptr);
    ~living_room();

private slots:

    void on_On_TV_Btn_clicked();

    void on_Off_TV_Btn_clicked();

    void on_up_volume_Btn_clicked();

    void on_down_volume_Btn_clicked();

    void on_LAMP_Btn_clicked();

    void on_TV_Btn_clicked();

    void on_AC_Btn_clicked();

    void on_On_AC_Btn_clicked();

    void on_Off_AC_Btn_clicked();

    void on_up_AC_Btn_clicked();

    void on_down_AC_Btn_clicked();

    void on_On_LAMP_Btn_clicked();

    void on_Off_LAMP_Btn_clicked();

    void on_PW_LAMP_hS_valueChanged(int value);

    void on_logout_living_Btn_clicked();

    void on_upgrate_living_Btn_clicked();

    void on_previus_TV_Btn_clicked();

    void on_On_LAMP_red_Btn_clicked();

    void on_On_LAMP_yellow_Btn_clicked();

    void on_On_LAMP_blue_Btn_clicked();

    void on_next_TV_Btn_clicked();



private:
    Ui::living_room *ui;
    int TV=0;
    int temp = 10;
    QString line[100];
    int i = 0;
    // read sumline from file text
    int sumline = 0;
    int KenhTV = 0;
    int color = 0;
    int brightness = 0;
    void readStatuswhenWrite();
    QString filename = "D:/Study/N04_HK1/C++/Qt/app/filetext/living.txt";

};

#endif // LIVING_ROOM_H
