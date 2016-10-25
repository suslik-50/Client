/********************************************************************************
** Form generated from reading UI file 'setting.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTING_H
#define UI_SETTING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Setting
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *Ip;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *Port;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *BtExit;
    QPushButton *BtSave;
    QPushButton *BtOk;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *Setting)
    {
        if (Setting->objectName().isEmpty())
            Setting->setObjectName(QStringLiteral("Setting"));
        Setting->resize(504, 342);
        centralwidget = new QWidget(Setting);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout->addWidget(label);

        Ip = new QLineEdit(centralwidget);
        Ip->setObjectName(QStringLiteral("Ip"));

        verticalLayout->addWidget(Ip);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        Port = new QLineEdit(centralwidget);
        Port->setObjectName(QStringLiteral("Port"));

        verticalLayout_2->addWidget(Port);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        BtExit = new QPushButton(centralwidget);
        BtExit->setObjectName(QStringLiteral("BtExit"));

        horizontalLayout_2->addWidget(BtExit);

        BtSave = new QPushButton(centralwidget);
        BtSave->setObjectName(QStringLiteral("BtSave"));

        horizontalLayout_2->addWidget(BtSave);

        BtOk = new QPushButton(centralwidget);
        BtOk->setObjectName(QStringLiteral("BtOk"));

        horizontalLayout_2->addWidget(BtOk);


        gridLayout->addLayout(horizontalLayout_2, 3, 1, 1, 1);

        Setting->setCentralWidget(centralwidget);
        label->raise();
        label_2->raise();
        Ip->raise();
        Port->raise();
        label->raise();
        label_2->raise();
        BtExit->raise();
        BtOk->raise();
        BtExit->raise();
        menubar = new QMenuBar(Setting);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 504, 20));
        Setting->setMenuBar(menubar);
        statusbar = new QStatusBar(Setting);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        Setting->setStatusBar(statusbar);

        retranslateUi(Setting);

        QMetaObject::connectSlotsByName(Setting);
    } // setupUi

    void retranslateUi(QMainWindow *Setting)
    {
        Setting->setWindowTitle(QApplication::translate("Setting", "MainWindow", 0));
        label->setText(QApplication::translate("Setting", "Ip \320\260\320\264\321\200\320\265\321\201", 0));
        label_2->setText(QApplication::translate("Setting", "Port", 0));
        BtExit->setText(QApplication::translate("Setting", "\320\222\321\213\321\205\320\276\320\264", 0));
        BtSave->setText(QApplication::translate("Setting", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", 0));
        BtOk->setText(QApplication::translate("Setting", "\320\236\320\272", 0));
    } // retranslateUi

};

namespace Ui {
    class Setting: public Ui_Setting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTING_H
