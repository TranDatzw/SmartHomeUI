#ifndef BED_ROOM_H
#define BED_ROOM_H

#include <QDialog>

namespace Ui {
class bed_room;
}

class bed_room : public QDialog
{
    Q_OBJECT

public:
    explicit bed_room(QWidget *parent = nullptr);
    ~bed_room();

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

    void on_logout_bed_Btn_clicked();

    void on_upgrate_bed_Btn_clicked();

    void on_previus_TV_Btn_clicked();

    void on_next_volume_Btn_clicked();

    void on_On_LAMP_red_Btn_clicked();

    void on_On_LAMP_yellow_Btn_clicked();

    void on_On_LAMP_blue_Btn_clicked();

private:
    Ui::bed_room *ui;
    int TV=0;
    int temp = 0;
    QString line[100];
    int i = 0;
    // read sumline from file text
    int sumline = 0;
    int KenhTV = -1;
    int color = 0;
    int brightness = 0;
    void readStatuswhenWrite();
    QString filename = "D:/Study/N04_HK1/C++/Qt/app/filetext/bed.txt";
};

#endif // BED_ROOM_H
