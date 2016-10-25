#ifndef SETTING_H
#define SETTING_H

#include <QMainWindow>
#include <QSettings>

namespace Ui {
class Setting;
}

class Setting : public QMainWindow
{
    Q_OBJECT

public:
    Setting(QWidget *parent = 0);
    ~Setting();

private slots:
    void on_BtExit_clicked();
    void on_BtSave_clicked();
    void on_BtOk_clicked();

private:
    Ui::Setting *ui;
    void saveSetting();
    void loadSetting();
    void validator();
};

#endif // SETTING_H
