#include "pageconfig.h"
#include "qdebug.h"
#include "ui_pageconfig.h"

int PageConfig::InveTableMaxRow = 10;
int PageConfig::AddDays=10;
int PageConfig::OrdTableMaxRow=10;
int PageConfig::VipTableMaxRow=10;
PageConfig::PageConfig(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PageConfig)
{
    ui->setupUi(this);

   // 获取运行目录
    QDir dir(QCoreApplication::applicationDirPath());
    QString settingsFilePath = dir.filePath("app_settings.ini");
    setting=new QSettings(settingsFilePath,QSettings::IniFormat);

    //InveTableMaxRow
    InveTableMaxRow=loadSettings(InveTableMaxRowName).toInt();
    if(InveTableMaxRow==0)
    {
        InveTableMaxRow=10;
        saveSettings(InveTableMaxRowName, InveTableMaxRow);
    }
    ui->spinBoxInveMaxShowRow->setValue(InveTableMaxRow);

    //AddDays
    AddDays=loadSettings(AddDaysName).toInt();
    ui->spinBoxAddDays->setValue(AddDays);

    //OrdTableMaxRow
    OrdTableMaxRow=loadSettings(OrdTableMaxRowName).toInt();
    if(OrdTableMaxRow==0)
    {
        OrdTableMaxRow=10;
        saveSettings(OrdTableMaxRowName,OrdTableMaxRow);
    }
    ui->spinBoxOrdMaxShowRow->setValue(OrdTableMaxRow);

    VipTableMaxRow=loadSettings(VipTableMaxRowName).toInt();
    if(VipTableMaxRow==0)
    {
        VipTableMaxRow=10;
        saveSettings(VipTableMaxRowName,VipTableMaxRow);
    }
    ui->spinBoxVipMaxShowRow->setValue(VipTableMaxRow);
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

void PageConfig::on_spinBoxInveMaxShowRow_valueChanged(int arg1)
{
    InveTableMaxRow=arg1;
    saveSettings(InveTableMaxRowName, InveTableMaxRow);
}

void PageConfig::on_spinBoxOrdMaxShowRow_valueChanged(int arg1)
{
    OrdTableMaxRow=arg1;
    saveSettings(OrdTableMaxRowName, OrdTableMaxRow);
}


void PageConfig::on_spinBoxAddDays_valueChanged(int arg1)
{
    AddDays=arg1;
    saveSettings(AddDaysName,AddDays);
}

void PageConfig::on_spinBoxVipMaxShowRow_valueChanged(int arg1)
{
    VipTableMaxRow=arg1;
    saveSettings(VipTableMaxRowName,VipTableMaxRow);
}


//static方法
int PageConfig::getInveTableMaxRow()
{
    return InveTableMaxRow;
}

int PageConfig::getAddDays()
{
    return AddDays;
}

int PageConfig::getOrdTableMaxRow()
{
    return  OrdTableMaxRow;
}

int PageConfig::getVipTableMaxRow()
{
    return VipTableMaxRow;
}


