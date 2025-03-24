#include "menu2.h"
#include "ui_menu2.h"
#include <QStandardItemModel>
#include <QMessageBox>
#include "login.h"

menu2::menu2(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::menu2)
    , head(nullptr)
    , length(0)
{
    ui->setupUi(this);
    this->setWindowTitle("单链表学生系统");

    // 初始化学生数据
    Student1 students[7] = {
        {"2023001", "张三", "计算机科学", "1班", "男", 20},
        {"2023003", "李四", "软件工程",   "2班", "女", 21},
        {"2023002", "王五", "人工智能",   "3班", "男", 19},
        {"2023004", "赵六", "数据科学",   "4班", "女", 19},
        {"2023015", "陈七", "网络安全",   "5班", "男", 22},
        {"2023006", "周八", "物联网",     "6班", "女", 20},
        {"2023017", "孙九", "数字媒体",   "7班", "男", 18}
    };

    // 尾插法初始化链表
    Node* tail = nullptr;
    for(int i = 0; i < 7; ++i) {
        Node* newNode = new Node(students[i]);
        if(!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        length++;
    }

    // 初始刷新
    refreshTable1();

    // 初始化表格列
    QStringList headers{"学号", "姓名", "专业", "班级", "性别", "年龄"};
    ui->tableWidget1->setColumnCount(headers.size());
    ui->tableWidget1->setHorizontalHeaderLabels(headers);

    // 初始刷新
    refreshTable1();

}

menu2::~menu2()
{
    delete ui;
}

//一键排序 冒泡排序实现
void menu2::on_pushButton_sort2_clicked()
{
    if(head == nullptr || head->next == nullptr) return;

    bool swapped;
    Node** ptr;

    // 外层循环控制遍历次数
    do {
        swapped = false;
        ptr = &head;

        // 内层循环进行比较交换
        while((*ptr)->next != nullptr) {
            Node* current = *ptr;
            Node* nextNode = current->next;

            // 比较学号大小
            if(current->data.id > nextNode->data.id) {
                // 交换节点位置
                current->next = nextNode->next;
                nextNode->next = current;
                *ptr = nextNode;
                swapped = true;
            }
            ptr = &(*ptr)->next;
        }
    } while(swapped);


    refreshTable1();
}



//合并
void menu2::on_pushButton_mer_clicked()
{
    // 初始化第二个链表（包含5个学生）
    Node* head2 = nullptr;
    Node* tail2 = nullptr;
    Student1 students2[5] = {
        {"2024001", "赵六", "计算机科学", "4班", "男", 22},
        {"2024005", "陈七", "软件工程", "5班", "女", 23},
        {"2024003", "孙八", "人工智能", "6班", "男", 20},
        {"2024002", "周九", "网络工程", "7班", "女", 21},
        {"2023002", "王五", "人工智能", "3班", "男", 19}
    };

    // 尾插法创建第二个链表
    for(int i = 0; i < 5; ++i) {
        Node* newNode = new Node(students2[i]);
        if(!head2) {
            head2 = tail2 = newNode;
        } else {
            tail2->next = newNode;
            tail2 = newNode;
        }
    }

    // 遍历第二个链表进行合并
    Node* current = head2;
    int addedCount = 0;  // 新增节点计数器

    while(current) {
        Node* nextNode = current->next;  // 提前保存下一节点
        current->next = nullptr;         // 断开当前节点连接

        // 在第一个链表中查找是否存在相同学号
        bool exists = false;
        Node* p = head;
        while(p) {
            if(p->data.id == current->data.id) {
                exists = true;
                break;
            }
            p = p->next;
        }

        // 不存在时执行插入操作
        if(!exists) {
            // 寻找第一个链表尾节点
            Node* tail1 = head;
            if(tail1) {
                while(tail1->next) tail1 = tail1->next;
                tail1->next = current;  // 尾插法
            } else {
                head = current;         // 第一个链表为空的情况
            }
            addedCount++;
            length++;
        } else {
            delete current;  // 释放重复节点内存
        }
        current = nextNode;  // 处理下一节点
    }

    // 刷新显示
    refreshTable1();
    QMessageBox::information(this, "提示",
                             QString("合并完成，新增%1条记录").arg(addedCount));
}

//刷新函数封装
void menu2::refreshTable1(){
    // 清空现有数据
    ui->tableWidget1->setRowCount(0);

    // 遍历链表填充数据
    Node* current = head;
    while(current != nullptr) {
        // 添加新行
        int row = ui->tableWidget1->rowCount();
        ui->tableWidget1->insertRow(row);

        // 填充单元格
        ui->tableWidget1->setItem(row, 0, new QTableWidgetItem(current->data.id));
        ui->tableWidget1->setItem(row, 1, new QTableWidgetItem(current->data.name));
        ui->tableWidget1->setItem(row, 2, new QTableWidgetItem(current->data.major));
        ui->tableWidget1->setItem(row, 3, new QTableWidgetItem(current->data.className));
        ui->tableWidget1->setItem(row, 4, new QTableWidgetItem(current->data.gender));
        ui->tableWidget1->setItem(row, 5,
                                  new QTableWidgetItem(QString::number(current->data.age)));

        current = current->next;
    }
}

// 刷新功能实现
void menu2::on_pushButton_renew_clicked()
{
    refreshTable1();
}


//添加
void menu2::on_pushButton_ad_clicked(){
    // 获取输入框内容
    QString id = ui->lineEdit_ad1->text().trimmed();
    QString name = ui->lineEdit_ad2->text().trimmed();
    QString major = ui->lineEdit_ad3->text().trimmed();
    QString className = ui->lineEdit_ad4->text().trimmed();
    QString gender = ui->lineEdit_ad5->text().trimmed();
    QString ageStr = ui->lineEdit_ad6->text().trimmed();

    // 输入验证
    if(id.isEmpty() || name.isEmpty() || major.isEmpty() ||
        className.isEmpty() || gender.isEmpty() || ageStr.isEmpty())
    {
        QMessageBox::warning(this, "输入错误", "所有字段必须填写");
        return;
    }

    // 转换年龄
    bool ok;
    int age = ageStr.toInt(&ok);
    if(!ok || age <= 0)
    {
        QMessageBox::warning(this, "输入错误", "年龄必须为正整数");
        return;
    }

    // 创建新学生节点
    Student1 newStudent;
    newStudent.id = id;
    newStudent.name = name;
    newStudent.major = major;
    newStudent.className = className;
    newStudent.gender = gender;
    newStudent.age = age;

    // 创建链表节点
    Node* newNode = new Node(newStudent);

    // 插入链表（尾插法）
    if(head == nullptr)//链表为空时
    {
        head = newNode;//头指针指向新节点
    }
    else
    {
        Node* current = head;
        while(current->next != nullptr)//遍历寻找最后一个节点
        {
            current = current->next;
        }
        current->next = newNode;// 将新节点挂到链表末尾
    }
    length++;

    refreshTable1();
    // 清空输入框
    ui->lineEdit_ad1->clear();
    ui->lineEdit_ad2->clear();
    ui->lineEdit_ad3->clear();
    ui->lineEdit_ad4->clear();
    ui->lineEdit_ad5->clear();
    ui->lineEdit_ad6->clear();
}


//根据学生学号删除学生信息
void menu2::on_pushButton_de_clicked()
{
    // 获取输入的学号
    QString targetId = ui->lineEdit_de1->text().trimmed();

    if(targetId.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入要删除的学号");
        return;
    }

    // 链表为空的情况处理
    if(head == nullptr) {
        QMessageBox::information(this, "提示", "学生列表为空");
        return;
    }

    Node* prev = nullptr;
    Node* current = head;
    bool found = false;

    // 遍历链表查找目标
    while(current != nullptr) {
        if(current->data.id == targetId) {
            found = true;

            // 调整链表指针
            if(prev == nullptr) {  // 删除头节点
                head = current->next;
            } else {  // 删除中间或尾节点
                prev->next = current->next;
            }

            // 释放内存并更新长度
            delete current;
            length--;
            break;
        }
        prev = current;
        current = current->next;
    }

    // 更新界面
    if(found) {
        refreshTable1();
        QMessageBox::information(this, "成功", "学生信息已删除");
        ui->lineEdit_de1->clear();
    } else {
        QMessageBox::warning(this, "错误", "未找到该学号的学生");
    }
}


//修改学生信息
void menu2::on_pushButton_cha_clicked()
{
    // 获取输入的学号
    QString targetId = ui->lineEdit_cha1->text().trimmed();
    if(targetId.isEmpty()){
        QMessageBox::warning(this, "输入错误", "请输入要修改的学生学号");
        return;
    }

    // 查找目标学生
    Node* current = head;
    while(current != nullptr){
        if(current->data.id == targetId) break;
        current = current->next;
    }

    if(current == nullptr){
        QMessageBox::warning(this, "错误", "未找到该学号的学生");
        return;
    }

    // 获取新输入的信息
    QString newName = ui->lineEdit_cha2->text().trimmed();
    QString newMajor = ui->lineEdit_cha3->text().trimmed();
    QString newClass = ui->lineEdit_cha4->text().trimmed();
    QString newGender = ui->lineEdit_cha5->text().trimmed();
    QString newAgeStr = ui->lineEdit_cha6->text().trimmed();

    // 输入验证
    if(newName.isEmpty() || newMajor.isEmpty() ||
        newClass.isEmpty() || newGender.isEmpty() || newAgeStr.isEmpty())
    {
        QMessageBox::warning(this, "输入错误", "所有字段必须填写");
        return;
    }

    bool ok;
    int newAge = newAgeStr.toInt(&ok);
    if(!ok || newAge <= 0){
        QMessageBox::warning(this, "输入错误", "年龄必须为正整数");
        return;
    }

    // 更新学生信息
    current->data.name = newName;
    current->data.major = newMajor;
    current->data.className = newClass;
    current->data.gender = newGender;
    current->data.age = newAge;

    // 刷新表格显示
    refreshTable1();

    // 清空输入框
    ui->lineEdit_cha1->clear();
    ui->lineEdit_cha2->clear();
    ui->lineEdit_cha3->clear();
    ui->lineEdit_cha4->clear();
    ui->lineEdit_cha5->clear();
    ui->lineEdit_cha6->clear();

    QMessageBox::information(this, "成功", "学生信息已修改");
}



//查询学生信息
void menu2::on_pushButton_6_clicked()
{
    // 获取输入的学号
    QString targetId = ui->lineEdit_fin1->text().trimmed();

    // 输入验证
    if(targetId.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入要查询的学号");
        return;
    }

    // 遍历链表查找学生
    Node* current = head;
    while(current != nullptr) {
        if(current->data.id == targetId) {
            // 找到学生，填充信息到对应输入框
            ui->lineEdit_fin2->setText(current->data.name);
            ui->lineEdit_fin3->setText(current->data.major);
            ui->lineEdit_fin4->setText(current->data.className);
            ui->lineEdit_fin5->setText(current->data.gender);
            ui->lineEdit_fin6->setText(QString::number(current->data.age));
            return; // 找到后直接返回
        }
        current = current->next;
    }

    // 未找到学生的情况处理
    QMessageBox::warning(this, "查询失败", "未找到该学号的学生");

    // 清空查询结果展示框
    ui->lineEdit_fin2->clear();
    ui->lineEdit_fin3->clear();
    ui->lineEdit_fin4->clear();
    ui->lineEdit_fin5->clear();
    ui->lineEdit_fin6->clear();
}

//返回主菜单
void menu2::on_pushButton_return_clicked()
{
    // 创建菜单界面
    login *w1 = new login();
    w1->show();

    // 关闭登录窗口
    this->accept();
}

