#include "pageconfig.h"
#include "ui_pageconfig.h"
int PageConfig::TableMaxRow = 10;
int PageConfig::AddDays=10;
PageConfig::PageConfig(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageConfig)
{
    ui->setupUi(this);

   // 获取运行目录
    QDir dir(QCoreApplication::applicationDirPath());
    QString settingsFilePath = dir.filePath("app_settings.ini");
    setting=new QSettings(settingsFilePath,QSettings::IniFormat);

    //TableMaxRow
    TableMaxRow=loadSettings(TableMaxRowName).toInt();
    if(TableMaxRow==0)
    {
        TableMaxRow=10;
        saveSettings(TableMaxRowName, TableMaxRow);
    }
    ui->spinBoxMaxShowRow->setValue(TableMaxRow);

    //AddDays
    AddDays=loadSettings(AddDaysName).toInt();
    if(AddDays==0)
    {
        AddDays=10;
        saveSettings(AddDaysName,AddDays);
    }
    ui->spinBoxAddDays->setValue(AddDays);

}

PageConfig::~PageConfig()
{
    delete setting;
    delete ui;
}

void PageConfig::saveSettings(const QString &key, const QVariant &value)
{
    setting->setValue(key,value);
}

QVariant PageConfig::loadSettings(const QString &key)
{
    return setting->value(key);
}

void PageConfig::on_spinBoxMaxShowRow_valueChanged(int arg1)
{
    TableMaxRow=arg1;
    saveSettings(TableMaxRowName, TableMaxRow);
}

void PageConfig::on_spinBoxAddDays_valueChanged(int arg1)
{
    AddDays=arg1;
    saveSettings(AddDaysName,AddDays);
}

//static方法
int PageConfig::getTableMaxRow()
{
    return TableMaxRow;
}

int PageConfig::getAddDays()
{
    return AddDays;
}



