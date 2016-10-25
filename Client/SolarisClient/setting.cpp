#include "setting.h"
#include "ui_setting.h"

Setting::Setting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Setting)
{
    ui->setupUi(this);
    setWindowTitle("Настройки");
    loadSetting();
    validator();
}

Setting::~Setting()
{
    delete ui;
}

void Setting::saveSetting()
{
    QSettings settings("TEXKOM", "Solaris");
    settings.beginGroup("Tcp");
    settings.setValue("IdAddres", this->ui->Ip->text());
    settings.setValue("Port", this->ui->Port->text());
    settings.endGroup();
}

void Setting::loadSetting()
{
    QSettings settings("TEXKOM", "Solaris");
    settings.beginGroup("Tcp");
    QString ipAdreas = settings.value("IdAddres").toString();
    QString port = settings.value("Port").toString();
    this->ui->Ip->setText(ipAdreas);
    this->ui->Port->setText(port);
    settings.endGroup();
}

void Setting::validator()
{
    QString ipRange = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    QRegExp ipRegex ("^" + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange
                     + "\\." + ipRange + "$");
    QRegExpValidator *ipValidator = new QRegExpValidator(ipRegex, this);
    this->ui->Ip->setValidator(ipValidator);

    QRegExp regExp("[0-9]{4}");
    QRegExpValidator* exp = new QRegExpValidator(regExp,this);
    this->ui->Port->setValidator(exp);
}

void Setting::on_BtExit_clicked()
{
   this->close();
}

void Setting::on_BtSave_clicked()
{
    saveSetting();
}

void Setting::on_BtOk_clicked()
{
    saveSetting();
    this->close();
}
