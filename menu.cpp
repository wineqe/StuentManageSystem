#include "menu.h"
#include "qundostack.h"
#include "ui_menu.h"
#include <QMessageBox>
#include <QHeaderView>
#include "login.h"


menu::menu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::menu)
    , undoStack(new QUndoStack(this))
{
    ui->setupUi(this);
    this->setWindowTitle("顺序表学生系统");

    // 初始化表格
    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setHorizontalHeaderLabels(
        {"学号", "姓名", "专业", "班级", "性别", "年龄"});
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 初始化顺序表
    const int INIT_SIZE = 10000;
    students.elem = new Student[INIT_SIZE];  // 分配初始内存
    students.length = 0;
    students.listSize = INIT_SIZE;

    // 添加初始数据
    students.elem[0] = {"2023001", "张三", "计算机科学", "1班", "男", 20};
    students.elem[1] = {"2023010", "李四", "软件工程", "2班", "女", 19};
    students.elem[2] = {"2023003", "王五", "人工智能", "3班", "男", 21};
    students.elem[3] = {"2023014", "赵六", "数据科学", "4班", "女", 19};
    students.elem[4] = {"2023005", "陈七", "网络安全", "5班", "男", 20};
    students.elem[5] = {"2023026", "刘八", "物联网",   "6班", "女", 22};
    students.elem[6] = {"2023007", "周九", "大数据",   "7班", "男", 18};
    students.length = 7;  // 更新实际元素数量

    refreshTable(); // 初始刷新表格
}

// 刷新表格函数
void menu::refreshTable()
{
    ui->tableWidget->setRowCount(0); // 清空表格

    for(int i = 0; i < students.length; ++i) {  //
        const Student& stu = students.elem[i];  // 访问数组元素

        int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);

        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(stu.id));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(stu.name));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(stu.major));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(stu.className));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(stu.gender));
        ui->tableWidget->setItem(row, 5,
                                 new QTableWidgetItem(QString::number(stu.age)));
    }
}

menu::~menu()
{
    delete ui;
}

// 添加学生信息功能实现
void menu::on_pushButton_add_clicked()
{
    // 获取输入框内容
    QString id = ui->lineEdit_add1->text().trimmed();
    QString name = ui->lineEdit_add2->text().trimmed();
    QString major = ui->lineEdit_add3->text().trimmed();
    QString className = ui->lineEdit_add4->text().trimmed();
    QString gender = ui->lineEdit_add5->text().trimmed();
    QString ageStr = ui->lineEdit_add6->text().trimmed();

    // 数据校验
    if (id.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "学号不能为空");
        ui->lineEdit_add1->setFocus();
        return;
    }
    if (name.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "姓名不能为空");
        ui->lineEdit_add2->setFocus();
        return;
    }

    // // 检查学号是否已存在
    // if (LocateElem(id) != -1) {
    //     QMessageBox::warning(this, "添加失败", "该学号已存在");
    //     ui->lineEdit_add1->selectAll();
    //     ui->lineEdit_add1->setFocus();
    //     return;
    // }

    // 转换年龄
    bool ok;
    int age = ageStr.toInt(&ok);
    if (!ok || age <= 0) {
        QMessageBox::warning(this, "输入错误", "年龄必须为正整数");
        ui->lineEdit_add6->selectAll();
        ui->lineEdit_add6->setFocus();
        return;
    }

    // 检查存储空间
    if (students.length >= students.listSize) {
        // 动态扩容（每次扩大2倍）
        int newSize = students.listSize * 2;
        Student* newSpace = new Student[newSize];
        memcpy(newSpace, students.elem, students.length * sizeof(Student));
        delete[] students.elem;
        students.elem = newSpace;
        students.listSize = newSize;
    }

    // 创建新学生记录
    Student newStudent{
        id,
        name,
        major,
        className,
        gender,
        age
    };

    // 插入到顺序表末尾
    students.elem[students.length] = newStudent;
    students.length++;

    // 刷新表格显示
    refreshTable();

    // 清空输入框
    ui->lineEdit_add1->clear();
    ui->lineEdit_add2->clear();
    ui->lineEdit_add3->clear();
    ui->lineEdit_add4->clear();
    ui->lineEdit_add5->clear();
    ui->lineEdit_add6->clear();

    QMessageBox::information(this, "操作成功", "学生信息添加成功");
}

// 排序功能实现
void menu::on_pushButton_clicked()
{
    // 检查数据是否为空
    if (students.length == 0) {
        QMessageBox::information(this, "提示", "没有需要排序的数据");
        return;
    }

    // 或者使用冒泡排序实现
    for (int i = 0; i < students.length - 1; ++i) {
        for (int j = 0; j < students.length - i - 1; ++j) {
            if (students.elem[j].id > students.elem[j+1].id) {
                // 交换元素
                Student temp = students.elem[j];
                students.elem[j] = students.elem[j+1];
                students.elem[j+1] = temp;
            }
        }
    }

    refreshTable(); // 刷新表格显示
    QMessageBox::information(this, "操作成功", "已按学号升序排序");
}

//根据学号删除学生信息
void menu::on_pushButton_delete_clicked()
{
    // 获取输入的学号并去除首尾空格
    QString id = ui->lineEdit_del1->text().trimmed();

    // 校验学号是否为空
    if (id.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "学号不能为空");
        ui->lineEdit_del1->setFocus();
        return;
    }

    // 遍历顺序表查找学生
    int index = -1;
    for (int i = 0; i < students.length; ++i) {
        if (students.elem[i].id == id) {
            index = i;
            break;
        }
    }

    // 未找到对应学号的处理
    if (index == -1) {
        QMessageBox::warning(this, "删除失败", "未找到该学号的学生");
        ui->lineEdit_del1->selectAll();
        ui->lineEdit_del1->setFocus();
        return;
    }

    // 执行删除操作：将后续元素前移
    for (int i = index; i < students.length - 1; ++i) {
        students.elem[i] = students.elem[i + 1];
    }
    students.length--; // 更新顺序表长度

    refreshTable(); // 刷新表格显示最新数据
    ui->lineEdit_del1->clear(); // 清空输入框
    QMessageBox::information(this, "操作成功", "学生信息删除成功");
}

void menu::on_pushButton_change_clicked()
{
    // 获取输入的学号并校验
    QString id = ui->lineEdit_ch1->text().trimmed();
    if (id.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "学号不能为空");
        ui->lineEdit_ch1->setFocus();
        return;
    }

    // 查找学生索引
    int index = -1;
    for (int i = 0; i < students.length; ++i) {
        if (students.elem[i].id == id) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        QMessageBox::warning(this, "修改失败", "未找到该学号的学生");
        ui->lineEdit_ch1->selectAll();
        ui->lineEdit_ch1->setFocus();
        return;
    }

    // 获取各个字段的新值
    Student &stu = students.elem[index];
    QString newName = ui->lineEdit_ch2->text().trimmed();
    QString newMajor = ui->lineEdit_ch3->text().trimmed();
    QString newClassName = ui->lineEdit_ch4->text().trimmed();
    QString newGender = ui->lineEdit_ch5->text().trimmed();
    QString newAgeStr = ui->lineEdit_ch6->text().trimmed();

    bool hasChange = false; // 记录是否有修改

    // 修改姓名（非空且不同时更新）
    if (!newName.isEmpty() && newName != stu.name) {
        stu.name = newName;
        hasChange = true;
    }

    // 修改专业
    if (!newMajor.isEmpty() && newMajor != stu.major) {
        stu.major = newMajor;
        hasChange = true;
    }

    // 修改班级
    if (!newClassName.isEmpty() && newClassName != stu.className) {
        stu.className = newClassName;
        hasChange = true;
    }

    // 修改性别
    if (!newGender.isEmpty() && newGender != stu.gender) {
        stu.gender = newGender;
        hasChange = true;
    }

    // 修改年龄
    if (!newAgeStr.isEmpty()) {
        bool ok;
        int newAge = newAgeStr.toInt(&ok);
        if (!ok || newAge <= 0) {
            QMessageBox::warning(this, "输入错误", "年龄必须为正整数");
            ui->lineEdit_ch6->selectAll();
            ui->lineEdit_ch6->setFocus();
            return;
        }
        if (newAge != stu.age) {
            stu.age = newAge;
            hasChange = true;
        }
    }

    // 检查是否有实际修改
    if (!hasChange) {
        QMessageBox::warning(this, "修改失败", "未提供有效修改内容");
        return;
    }

    refreshTable(); // 刷新表格显示
    // 清空所有输入框
    ui->lineEdit_ch1->clear();
    ui->lineEdit_ch2->clear();
    ui->lineEdit_ch3->clear();
    ui->lineEdit_ch4->clear();
    ui->lineEdit_ch5->clear();
    ui->lineEdit_ch6->clear();
    QMessageBox::information(this, "操作成功", "学生信息修改成功");
}

//查询功能实现
void menu::on_pushButton_find_clicked()
{
    // 获取输入的学号并去除首尾空格
    QString searchId = ui->lineEdit_ser1->text().trimmed();

    // 校验学号是否为空
    if (searchId.isEmpty()) {
        QMessageBox::warning(this, "输入错误", "请输入要查找的学号");
        ui->lineEdit_ser1->setFocus();
        return;
    }

    // 遍历顺序表查找学生
    bool found = false;
    Student target;
    for (int i = 0; i < students.length; ++i) {
        if (students.elem[i].id == searchId) {
            target = students.elem[i];
            found = true;
            break;
        }
    }

    if (!found) {
        QMessageBox::information(this, "查找结果", "未找到该学号的学生");
        // 清空输出框
        ui->lineEdit_ser2->clear();
        ui->lineEdit_ser3->clear();
        ui->lineEdit_ser4->clear();
        ui->lineEdit_ser5->clear();
        ui->lineEdit_ser6->clear();
        ui->lineEdit_ser1->selectAll();
        ui->lineEdit_ser1->setFocus();
        return;
    }

    // 在对应控件显示信息
    ui->lineEdit_ser2->setText(target.name);
    ui->lineEdit_ser3->setText(target.major);
    ui->lineEdit_ser4->setText(target.className);
    ui->lineEdit_ser5->setText(target.gender);
    ui->lineEdit_ser6->setText(QString::number(target.age));

    // 可选：高亮显示表格中的对应行
    for (int row = 0; row < ui->tableWidget->rowCount(); ++row) {
        if (ui->tableWidget->item(row, 0)->text() == searchId) {
            ui->tableWidget->selectRow(row);
            break;
        }
    }
}

//刷新
void menu::on_pushButton_refresh_clicked()
{
    // 刷新表格显示
    refreshTable();
}


void menu::on_lineEdit_add1_cursorPositionChanged(int arg1, int arg2){

}












void menu::on_pushButton_return2_clicked()
{
    // 创建菜单界面
    login *w2 = new login();
    w2->show();

    // 关闭登录窗口
    this->accept();
}

