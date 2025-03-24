#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "menu.h"
#include "menu2.h"
#include <QMessageBox>

login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("用户登录");

    // 设置密码输入框的回显模式
    ui->lineEdit_ps->setEchoMode(QLineEdit::Password);
}

login::~login()
{
    delete ui;
}

//退出程序按钮
void login::on_pushButton_exit_clicked()
{
    this->reject();  // 关闭对话框并返回QDialog::Rejected
    QApplication::quit(); // 退出应用程序
}

// 登录验证
bool login::validateUser(const QString &username, const QString &password)
{
    // 验证用户名和密码
    return (username == "cxq" && password == "123");
}

// 登录顺序表学生管理系统按钮
void login::on_pushButton_login_clicked()
{
    // 获取输入内容
    QString username = ui->lineEdit_id->text().trimmed();
    QString password = ui->lineEdit_ps->text();

    // 输入验证
    if(username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "用户名和密码不能为空");
        return;
    }

    // 身份验证
    if(validateUser(username, password)) {
        // 创建菜单界面
        menu *w = new menu();
        w->show();

        // 关闭登录窗口
        this->accept();
    } else {
        QMessageBox::critical(this, "登录失败", "用户名或密码错误");
        // 清空输入框
        ui->lineEdit_id->clear();
        ui->lineEdit_ps->clear();
        ui->lineEdit_id->setFocus();
    }
}

//登录单链表学生管理系统
void login::on_pushButton_login2_clicked()
{
    QString username = ui->lineEdit_id->text().trimmed();
    QString password = ui->lineEdit_ps->text();

    if(username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "用户名和密码不能为空");
        return;
    }

    if(validateUser(username, password)) {
        menu2 *w2 = new menu2();  // 跳转到新菜单
        // w2->setAttribute(Qt::WA_DeleteOnClose);
        w2->show();
        this->accept();
    } else {
        QMessageBox::critical(this, "登录失败", "用户名或密码错误");
        ui->lineEdit_id->clear();
        ui->lineEdit_ps->clear();
        ui->lineEdit_id->setFocus();
    }
}

void login::on_lineEdit_ps_cursorPositionChanged(int arg1, int arg2)
{

}


void login::on_lineEdit_id_cursorPositionChanged(int arg1, int arg2)
{

}


void login::on_pushButton_clicked()
{

}

