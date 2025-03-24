#ifndef MENU_H
#define MENU_H

#include <QDialog>
#pragma once
#include <QWidget>
#include <QString>
#include <vector>
#include <QUndoStack>
#include <QUndoView>
#include <QUndoCommand>

#define MAXSIZE 10000 // 初始数组大小

// 学生信息结构体
typedef struct {
    QString id;        // 学号
    QString name;      // 姓名
    QString major;     // 专业
    QString className; // 班级
    QString gender;    // 性别
    int age;           // 年龄
} Student;

// 顺序表结构体
typedef struct {
    Student *elem;     // 存储空间基址
    int length;        // 当前长度
    int listSize;      // 当前分配的存储容量
} SqList;

namespace Ui {
class menu;
}

class menu : public QDialog
{
    Q_OBJECT

public:
    explicit menu(QWidget *parent = nullptr);
    ~menu();

    void refreshTable();
    int LocateElem(QString id);                 // 按学号查找位置

private slots:
    void on_pushButton_clicked();

    void on_pushButton_add_clicked();

    void on_pushButton_delete_clicked();

    void on_pushButton_change_clicked();

    void on_pushButton_find_clicked();

    void on_pushButton_refresh_clicked();

    void on_lineEdit_add1_cursorPositionChanged(int arg1, int arg2);



    void on_pushButton_return2_clicked();

private:
    Ui::menu *ui;
    QUndoStack *undoStack;
     SqList students;                            // 学生顺序表

};

#endif // MENU_H
