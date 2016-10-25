#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QMainWindow>
#include <setting.h>
#include <QSettings>
#include <QTcpSocket>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QDateTime>
#include <QCoreApplication>
#include <QThread>
#include "structur.h"

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT
    Q_PROPERTY(QString ipAddres READ ipAddres WRITE setIpAddres NOTIFY ipAddresChanged)
    Q_PROPERTY(int port READ port WRITE setPort NOTIFY portChanged)

public:
    explicit Client(QWidget *parent = 0);
    ~Client();

    QString ipAddres() const;

    int port() const;

public slots:
    void setIpAddres(QString ipAddres);
    void setPort(int port);

signals:
    void ipAddresChanged(QString ipAddres);
    void portChanged(int port);

private slots:
    void on_Setting_triggered();
    void on_Connect_triggered();
    void on_Disconect_triggered();
    void slotConnect();
    void slotRead();
    void slotDisconnect();
    void on_Exit_triggered();
    void on_pushButton_clicked();

    void on_pushButton_20_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_13_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_12_clicked();

    void on_pushButton_14_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_15_clicked();

    void on_pushButton_16_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_18_clicked();

    void on_pushButton_19_clicked();

private:
    Ui::Client *ui;
    Setting* setting;
    QString m_ipAddres;
    int m_port;
    QTcpSocket* socket;
    quint16 m_nNextBlockSize;
    QStandardItemModel* model;
    qint16 countTbl = 0;
    void loadSetting();
    void connecttoserver();
    void setTableData();
    void newsetTableData(QString name, QString a, QString b, QString time);
    void pars(QStringList list);
    void combobox(QString name);
    int col;
    QStringList names;
    QList<solar_battery_salleter> Data[100];
    QString satelName;

    void sendServer(QString com);
    QString comand;
};

#endif // CLIENT_H
