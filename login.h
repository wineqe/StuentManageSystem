#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_exit_clicked();

    void on_pushButton_login_clicked();
    void on_pushButton_login2_clicked();

    void on_lineEdit_ps_cursorPositionChanged(int arg1, int arg2);

    void on_lineEdit_id_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_clicked();

private:
    Ui::login *ui;
    // 添加验证方法
    bool validateUser(const QString &username, const QString &password);
};

#endif // LOGIN_H
