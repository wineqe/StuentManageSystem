/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label_st;
    QLabel *label_id;
    QLineEdit *lineEdit_id;
    QLabel *label_ps;
    QLineEdit *lineEdit_ps;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_login;
    QPushButton *pushButton_login2;
    QPushButton *pushButton_exit;

    void setupUi(QDialog *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(373, 278);
        formLayoutWidget = new QWidget(login);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(20, 20, 331, 231));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setContentsMargins(0, 0, 0, 0);
        label_st = new QLabel(formLayoutWidget);
        label_st->setObjectName("label_st");

        formLayout->setWidget(0, QFormLayout::FieldRole, label_st);

        label_id = new QLabel(formLayoutWidget);
        label_id->setObjectName("label_id");

        formLayout->setWidget(1, QFormLayout::LabelRole, label_id);

        lineEdit_id = new QLineEdit(formLayoutWidget);
        lineEdit_id->setObjectName("lineEdit_id");

        formLayout->setWidget(1, QFormLayout::FieldRole, lineEdit_id);

        label_ps = new QLabel(formLayoutWidget);
        label_ps->setObjectName("label_ps");

        formLayout->setWidget(2, QFormLayout::LabelRole, label_ps);

        lineEdit_ps = new QLineEdit(formLayoutWidget);
        lineEdit_ps->setObjectName("lineEdit_ps");

        formLayout->setWidget(2, QFormLayout::FieldRole, lineEdit_ps);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_login = new QPushButton(formLayoutWidget);
        pushButton_login->setObjectName("pushButton_login");

        horizontalLayout->addWidget(pushButton_login);

        pushButton_login2 = new QPushButton(formLayoutWidget);
        pushButton_login2->setObjectName("pushButton_login2");

        horizontalLayout->addWidget(pushButton_login2);

        pushButton_exit = new QPushButton(formLayoutWidget);
        pushButton_exit->setObjectName("pushButton_exit");

        horizontalLayout->addWidget(pushButton_exit);


        formLayout->setLayout(3, QFormLayout::FieldRole, horizontalLayout);


        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QDialog *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Dialog", nullptr));
        label_st->setText(QCoreApplication::translate("login", "                    \345\255\246\347\224\237\344\277\241\346\201\257\347\256\241\347\220\206\347\263\273\347\273\237", nullptr));
        label_id->setText(QCoreApplication::translate("login", "\347\224\250\346\210\267ID", nullptr));
        label_ps->setText(QCoreApplication::translate("login", "\345\257\206   \347\240\201", nullptr));
        pushButton_login->setText(QCoreApplication::translate("login", "\347\231\273\345\275\225", nullptr));
        pushButton_login2->setText(QCoreApplication::translate("login", "\347\231\273\345\275\225\351\223\276\350\241\250\345\255\246\347\224\237\347\263\273\347\273\237", nullptr));
        pushButton_exit->setText(QCoreApplication::translate("login", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
