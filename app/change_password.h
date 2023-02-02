#ifndef CHANGE_PASSWORD_H
#define CHANGE_PASSWORD_H

#include <QDialog>

namespace Ui {
class change_password;
}

class change_password : public QDialog
{
    Q_OBJECT

public:
    explicit change_password(QWidget *parent = nullptr);
    ~change_password();

private slots:
    void on_logout_password_Btn_clicked();

    void on_save_password_Btn_clicked();

private:
    Ui::change_password *ui;
    QString filename = "D:/Study/N04_HK1/C++/Qt/app/filetext/text.txt";
};

#endif // CHANGE_PASSWORD_H
