/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QVBoxLayout *verticalLayout;
    QPushButton *btnNivel1;
    QPushButton *btnNivel2;

    void setupUi(QWidget *menu)
    {
        if (menu->objectName().isEmpty())
            menu->setObjectName("menu");
        menu->resize(400, 300);
        verticalLayout = new QVBoxLayout(menu);
        verticalLayout->setObjectName("verticalLayout");
        btnNivel1 = new QPushButton(menu);
        btnNivel1->setObjectName("btnNivel1");

        verticalLayout->addWidget(btnNivel1);

        btnNivel2 = new QPushButton(menu);
        btnNivel2->setObjectName("btnNivel2");

        verticalLayout->addWidget(btnNivel2);


        retranslateUi(menu);

        QMetaObject::connectSlotsByName(menu);
    } // setupUi

    void retranslateUi(QWidget *menu)
    {
        menu->setWindowTitle(QCoreApplication::translate("Menu", "Form", nullptr));
        btnNivel1->setText(QCoreApplication::translate("Menu", "Iniciar Nivel 1", nullptr));
        btnNivel2->setText(QCoreApplication::translate("Menu", "Iniciar Nivel 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
