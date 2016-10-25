#include "client.h"
#include "ui_client.h"
#include <QDateTime>

Client::Client(QWidget *parent) :
    QMainWindow(parent), m_nNextBlockSize(0),
    ui(new Ui::Client)
{
    ui->setupUi(this);

    setting = new Setting();
    this->setWindowTitle("Solaris");
    setWindowState(Qt::WindowMaximized);
    this->ui->label->setStyleSheet("color: rgb(255, 69, 0)");
    connecttoserver();
    setTableData();
}

Client::~Client()
{
    socket->close();
    socket->deleteLater();
    delete ui;
}

QString Client::ipAddres() const
{
    return m_ipAddres;
}

int Client::port() const
{
    return m_port;
}

void Client::setIpAddres(QString ipAddres)
{
    if (m_ipAddres == ipAddres)
        return;

    m_ipAddres = ipAddres;
    emit ipAddresChanged(ipAddres);
}

void Client::setPort(int port)
{
    if (m_port == port)
        return;

    m_port = port;
    emit portChanged(port);
}

void Client::loadSetting()
{
    QSettings settings("TEXKOM", "Solaris");
    settings.beginGroup("Tcp");
    QString ipAdreas = settings.value("IdAddres").toString();
    int port = settings.value("Port").toInt();
    setIpAddres(ipAdreas);
    setPort(port);
    settings.endGroup();
}

void Client::connecttoserver()
{
    socket  =   new QTcpSocket(this);
    connect(socket, &QTcpSocket::connected, this, &Client::slotConnect);
    connect(socket, &QTcpSocket::channelReadyRead, this, &Client::slotRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::slotDisconnect);
    socket->connectToHost(m_ipAddres, m_port);
}

void Client::slotConnect()
{
    ui->progressBar->setVisible(true);
    this->ui->label->setText("Подключен!");
    this->ui->label->setStyleSheet("color: rgb(127, 255, 0)");
    this->ui->Connect->setEnabled(false);
    this->ui->Disconect->setEnabled(true);

    for (int i = 0; i < 100; ++i) {
        ui->progressBar->setValue(i);
        QThread::msleep(100);
        qApp->processEvents();
    }
    ui->progressBar->setVisible(false);
}

void Client::slotRead()
{
    QStringList list;
    QString str;

    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_5);
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (socket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> m_nNextBlockSize;
        }
        if (socket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }
        in >> str >> list;
        qDebug() << str;
        m_nNextBlockSize = 0;
    }
    if (str == "tabel")
    {
        pars(list);
    }
    else
    {
        ui->textEdit->append(list[0]);
        qDebug() << list[0];
    }

}

void Client::pars(QStringList list)
{
    if (Data[0].length() == 100) {
        for (int i = 0; i < 100; ++i) {
            Data[i].clear();
        }
    }

    int leng = list.length();
    QString line, name, a, b, time;
    for (int i = 0; i < list.length(); ++i) {
        line += list[i];
    }

    list = line.split(",");
    line.clear();
    list.removeAt(list.length()-1);

    solar_battery_salleter satel;
    int i = 1, j = 0;
    foreach (QString item, list)
    {
        //qDebug() << item;
        if (i == 1)
        {
            name = item;
            i++;
            if (this->col != leng) {
                ui->comboBox->addItem(item);
            }
        } else
        if (i == 2)
        {
            a = item;
            i++;
        } else
        if (i == 3)
        {
            b = item;
            i++;
        } else
        if (i == 4)
        {
            time = item;
            i = 1;
            if (name == satelName)
            {
                newsetTableData(name, a, b, time);
            }
            satel.name = name;
            satel.a = a;
            satel.b = b;
            satel.time = time;
            this->Data[j].append(satel);
            j++;
        }
    }
    this->col = leng;
}

void Client::on_pushButton_clicked()
{
    satelName = ui->comboBox->currentText();
    model->clear();
    setTableData();
    this->countTbl=0;
    for (int i = 0; i < Data[i].size(); ++i) {
        if (Data[i][Data[i].size()-1].name == ui->comboBox->currentText())
        {
            for (int j = 0; j < Data[i].size(); ++j) {
                //qDebug() << Data[i][j].a;
                newsetTableData(Data[i][j].name, Data[i][j].a, Data[i][j].b, Data[i][j].time);
            }
        }
    }
}

void Client::combobox(QString name)
{
    ui->comboBox->addItem(name);
}

void Client::sendServer(QString com)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_5);
    out << quint16(0) << com;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    socket->write(arrBlock);
}


void Client::slotDisconnect()
{
    on_Disconect_triggered();
}

void Client::on_Setting_triggered()
{
    setting->show();
}

void Client::on_Connect_triggered()
{
    loadSetting();
    connecttoserver();

}

void Client::on_Disconect_triggered()
{
    this->ui->label->setText("Отключен!");
    this->ui->label->setStyleSheet("color: rgb(255, 69, 0)");
    this->ui->Connect->setEnabled(true);
    this->ui->Disconect->setEnabled(false);

    socket->close();
    socket->deleteLater();
}


void Client::on_Exit_triggered()
{
    setting->close();
    this->close();
}

void Client::setTableData()
{
    model = new QStandardItemModel(0, 4, this);
    this->ui->tableView->setModel(model);
    this->ui->tableView->setColumnWidth(0,100);
    this->ui->tableView->setColumnWidth(1,150);
    model->setHeaderData(0, Qt::Horizontal, "Спутник");
    model->setHeaderData(1, Qt::Horizontal, "Время");
    model->setHeaderData(2, Qt::Horizontal, "a");
    model->setHeaderData(3, Qt::Horizontal, "b");
}

void Client::newsetTableData(QString name, QString a, QString b, QString time)
{
    //qDebug() << a;
    ++countTbl;
    QString date, aa, bb, name2;
    QModelIndex index;
    model->setRowCount(countTbl);
    for (int row = model->rowCount(); row!=0 ; --row) {
        int i=0;
        index = model->index(row-1, i);
        name2 = model->data(index).toString();
        ++i;
        index = model->index(row-1, i);
        date = model->data(index).toString();
        ++i;
        index = model->index(row-1, i);
        aa = model->data(index).toString();
        ++i;
        index = model->index(row-1, i);
        bb = model->data(index).toString();

        i=0;
        index = model->index(row, i);
        model->setData(index, name2);
        ++i;
        index = model->index(row, i);
        model->setData(index, date);
        ++i;
        index = model->index(row, i);
        model->setData(index, aa);
        ++i;
        index = model->index(row, i);
        model->setData(index, bb);

    }

    index = model->index(0, 0);
    model->setData(index, name);

    index = model->index(0, 1);
    model->setData(index, time);

    index = model->index(0, 2);
    model->setData(index, a);

    index = model->index(0, 3);
    model->setData(index, b);
}



void Client::on_pushButton_20_clicked()
{
    //Очистка пула значений данных
    comand.clear();
    comand = "clean record_drain";
    sendServer(comand);
}

void Client::on_pushButton_2_clicked()
{
    //Debuge
    comand.clear();
    if (ui->checkBox->isChecked())
    {
        comand = "debug salleter true";
        sendServer(comand);
    }
    else
    {
        comand = "debug salleter false";
        sendServer(comand);
    }

    if (ui->checkBox_2->isChecked())
    {
        comand = "debug sun true";
        sendServer(comand);
    }
    else
    {
        comand = "debug sun false";
        sendServer(comand);
    }

    if (ui->checkBox_3->isChecked())
    {
        comand = "debug corners_solar_battery true";
        sendServer(comand);
    }
    else
    {
        comand = "debug corners_solar_battery false";
        sendServer(comand);
    }

    if (ui->checkBox_4->isChecked())
    {
        comand = "ddebug main_modul <true>";
        sendServer(comand);
    }
    else
    {
        comand = "debug main_modul <false>";
        sendServer(comand);
    }
}

void Client::on_pushButton_7_clicked()
{
    // интервал расчета спутника
    comand.clear();
    comand = "replay salleter " + ui->lineEdit_4->text();
    sendServer(comand);
    ui->lineEdit_4->clear();
}

void Client::on_pushButton_8_clicked()
{
    // интервал расчета солнца
    comand.clear();
    comand = "replay sun " + ui->lineEdit_5->text();
    sendServer(comand);
    ui->lineEdit_5->clear();
}

void Client::on_pushButton_5_clicked()
{
    // ТСП порт
    comand.clear();
    comand = "tcp port " + ui->lineEdit_2->text();
    sendServer(comand);
    ui->lineEdit_2->clear();
}

void Client::on_pushButton_6_clicked()
{
    // телнет порт
    comand.clear();
    comand = "telnet port " + ui->lineEdit_3->text();
    sendServer(comand);
    ui->lineEdit_3->clear();
}

void Client::on_pushButton_9_clicked()
{
    // Запуск потоков спутника
    comand.clear();
    comand = "start all salleter";
    sendServer(comand);
}

void Client::on_pushButton_11_clicked()
{
    // Запуск потока солнца
    comand.clear();
    comand = "start sun";
    sendServer(comand);
}

void Client::on_pushButton_13_clicked()
{
    // запуск потока спутника
    comand.clear();
    comand = "start salleter " + ui->lineEdit_6->text();
    sendServer(comand);
    ui->lineEdit_6->clear();
}

void Client::on_pushButton_10_clicked()
{
    // остановка потоков спутника
    comand.clear();
    comand = "stop all salleter";
    sendServer(comand);
}

void Client::on_pushButton_12_clicked()
{
    // остановка потока солнца
    comand.clear();
    comand = "stop sun";
    sendServer(comand);
}

void Client::on_pushButton_14_clicked()
{
    // остановить поток спутника
    comand.clear();
    comand = "stop salleter " + ui->lineEdit_7->text() ;
    sendServer(comand);
    ui->lineEdit_7->clear();
}


void Client::on_pushButton_3_clicked()
{
    // получить количество значений в пуле
    comand.clear();
    comand = "get count_record_drain";
    sendServer(comand);
}

void Client::on_pushButton_4_clicked()
{
    // Возращает углы а,b спутника
    comand.clear();
    comand = "get value_corners_salleter " + ui->lineEdit->text() ;
    sendServer(comand);
    ui->lineEdit->clear();
}



void Client::on_pushButton_15_clicked()
{
    // Удаляет поток спутника
    comand.clear();
    comand = "delete potoc salleter " + ui->lineEdit_8->text();
    sendServer(comand);
    ui->lineEdit_8->clear();
}

void Client::on_pushButton_16_clicked()
{
    // удаление спутника из базы дынных
    comand.clear();
    comand = "delete data salleter " + ui->lineEdit_8->text() ;
    sendServer(comand);
    ui->lineEdit_8->clear();
}

void Client::on_pushButton_17_clicked()
{
    //добавление нового спутника в бд и запуск расчетов
    comand.clear();
    comand = "new salleter_to_date_base " + ui->Name->text() + " " + ui->Time->text() + " " + ui->A->text() + " " + ui->I->text() + " " + ui->I->text() +
            " " + ui->Arg_per->text() + " " + ui->Dolgota->text() + " " + ui->M->text();
    sendServer(comand);
    sendServer(comand);
    ui->Name->clear();
    ui->Time->clear();
    ui->A->clear();
    ui->I->clear();
    ui->Arg_per->clear();
    ui->Dolgota->clear();
    ui->M->clear();
    ui->E->clear();
}

void Client::on_pushButton_18_clicked()
{
    //добавление нового спутника в бд
    comand.clear();
    comand = "new salleter_to_date_base " + ui->Name->text() + " " + ui->Time->text() + " " + ui->A->text() + " " + ui->I->text() + " " + ui->I->text() +
            " " + ui->Arg_per->text() + " " + ui->Dolgota->text() + " " + ui->M->text();
    sendServer(comand);
    sendServer(comand);
    ui->Name->clear();
    ui->Time->clear();
    ui->A->clear();
    ui->I->clear();
    ui->Arg_per->clear();
    ui->Dolgota->clear();
    ui->M->clear();
    ui->E->clear();
}

void Client::on_pushButton_19_clicked()
{
    //изменение  спутника в бд
    comand.clear();
    comand = "new salleter_to_date_base " + ui->Name->text() + " " + ui->Time->text() + " " + ui->A->text() + " " + ui->I->text() + " " + ui->I->text() +
            " " + ui->Arg_per->text() + " " + ui->Dolgota->text() + " " + ui->M->text();
    sendServer(comand);
    ui->Name->clear();
    ui->Time->clear();
    ui->A->clear();
    ui->I->clear();
    ui->Arg_per->clear();
    ui->Dolgota->clear();
    ui->M->clear();
    ui->E->clear();
}
