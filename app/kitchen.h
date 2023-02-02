#ifndef KITCHEN_H
#define KITCHEN_H

#include <QDialog>

namespace Ui {
class kitchen;
}

class kitchen : public QDialog
{
    Q_OBJECT

public:
    explicit kitchen(QWidget *parent = nullptr);
    ~kitchen();

private slots:
    void on_logout_kitchen_Btn_clicked();

    void on_On_Fri_Btn_clicked();

    void on_Off_Fri_Btn_clicked();

    void on_GAS_Btn_clicked();

    void on_On_GAS_Btn_clicked();

    void on_Off_GAS_Btn_clicked();

    void on_up_GAS_Btn_clicked();

    void on_down_GAS_Btn_clicked();

    void on_On_LAMP_Btn_clicked();

    void on_Off_LAMP_Btn_clicked();

    void on_On_LAMP_red_Btn_clicked();

    void on_On_LAMP_yellow_Btn_clicked();

    void on_On_LAMP_blue_Btn_clicked();

    void on_PW_LAMP_hS_valueChanged(int value);

    void on_Fri_Btn_clicked();

    void on_LAMP_Btn_clicked();

    void on_upgrate_kitchen_Btn_clicked();

private:
    Ui::kitchen *ui;
    int TV=0;
    int temp = 0;
    int level = 0;
    QString line[100];
    int i = 0;
    // read sumline from file text
    int sumline = 0;
    int KenhTV = -1;
    int color = 0;
    int brightness = 0;
    void readStatuswhenWrite();
    QString filename = "D:/Study/N04_HK1/C++/Qt/app/filetext/kitchen.txt";
};

#endif // KITCHEN_H
