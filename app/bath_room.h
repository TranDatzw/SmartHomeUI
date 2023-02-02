#ifndef BATH_ROOM_H
#define BATH_ROOM_H

#include <QDialog>

namespace Ui {
class bath_room;
}

class bath_room : public QDialog
{
    Q_OBJECT

public:
    explicit bath_room(QWidget *parent = nullptr);
    ~bath_room();

private slots:
    void on_logout_bath_clicked();

    void on_On_MS_Btn_clicked();

    void on_Off_MS_Btn_clicked();

    void on_up_volume_Btn_clicked();

    void on_down_volume_Btn_clicked();

    void on_LAMP_Btn_clicked();

    void on_MS_Btn_clicked();

    void on_WM_Btn_clicked();

    void on_On_WM_Btn_clicked();

    void on_Off_WM_Btn_clicked();

    void on_up_WM_Btn_clicked();

    void on_down_WM_Btn_clicked();

    void on_On_LAMP_Btn_clicked();

    void on_Off_LAMP_Btn_clicked();

    void on_PW_LAMP_hS_valueChanged(int value);

    void on_upgrate_bath_Btn_clicked();

    void on_previus_MS_Btn_clicked();

    void on_next_volume_Btn_clicked();

    void on_On_LAMP_red_Btn_clicked();

    void on_On_LAMP_yellow_Btn_clicked();

    void on_On_LAMP_blue_Btn_clicked();

    void on_logout_bath_Btn_clicked();

private:
    Ui::bath_room *ui;
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
    QString filename = "D:/Study/N04_HK1/C++/Qt/app/filetext/bath.txt";
};

#endif // BATH_ROOM_H
