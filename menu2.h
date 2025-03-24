#ifndef MENU2_H
#define MENU2_H
#include <QString>

#include <QDialog>

// 学生信息结构体
struct Student1 {
    QString id;        // 学号
    QString name;      // 姓名
    QString major;     // 专业
    QString className; // 班级
    QString gender;    // 性别
    int age;           // 年龄
};

namespace Ui {
class menu2;
}

class menu2 : public QDialog
{
    Q_OBJECT

public:
    explicit menu2(QWidget *parent = nullptr);
    ~menu2();
    void refreshTable1();

private slots:
    void on_pushButton_sort2_clicked();

    void on_pushButton_mer_clicked();

    void on_pushButton_renew_clicked();

    void on_pushButton_ad_clicked();

    void on_pushButton_de_clicked();

    void on_pushButton_cha_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_return_clicked();

private:
    Ui::menu2 *ui;

    // 单链表节点定义
    struct Node {
        Student1 data;   // 数据域：存储学生信息
        Node* next;     // 指针域：指向下一个节点

        // 节点构造函数
        Node(const Student1& student)
            : data(student), next(nullptr) {}
    };

    Node* head; // 链表头指针
    int length; // 链表长度计数器
};

#endif // MENU2_H
