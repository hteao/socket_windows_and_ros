#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QString"
#include "stdio.h"
#include <QSettings>
#include <QHostAddress>
#include <QDateTime>
#include <QMessageBox>
#define LOAD_CFG_VARIANT(x) cfg.value(#x,x)
#define SAVE_CFG_VARIANT(x) cfg.setValue(#x, x)

client::client(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::client)
{
    ui->setupUi(this);
    tcpsocket=new QTcpSocket(this);

}

client::~client()
{
    delete ui;
}

void client::connected_SLOT()
{
    connect(tcpsocket,SIGNAL(readyRead()),this,SLOT(readyRead_Slot()));//将信号连接到槽
    connect(tcpsocket,SIGNAL(connected()),this,SLOT(connected_SLOT()));
}
void client::on_connect_sever_clicked()
{
  tcpsocket->connectToHost(ui->ipnum->text(),ui->portnum->text().toUInt());//转为无符号，连接服务器端口
  connect(tcpsocket,SIGNAL(connected()),this,SLOT(connected_SLOT()));
  savecfg();
  qDebug()<<"连接服务器 ";
}
void client::readyRead_Slot()//定义接收信号的槽
{


    QByteArray buf;
    buf=tcpsocket->readAll();//接收由tcp发送过来的信息
    buf="recive:"+buf;
    if(strnlen(buf,10)>7)
    {
      ui->receivewd->append(buf);
    }

}



void client::on_closeclient_clicked()
{
    tcpsocket->close();
    qDebug()<<"shutdown the device ";
    QApplication* app;
    app->exit(0);

}

void client::on_sent_clicked()
{
    tcpsocket->connectToHost(ui->ipnum->text(),ui->portnum->text().toUInt());//转为无符号，连接服务器端口
    tcpsocket->write(ui->content->text().toUtf8().data());
}
/**勾选记住密码,定义一个标志位*/
void client::on_Rem_ip_port_clicked()
{
        remeberPasswd= true;

}

/**保存登录信息**/
void client::savecfg()
{
    QSettings cfg("ip_port_config.ini",QSettings::IniFormat);
    ip= ui->ipnum->text();
    port= ui->portnum->text();
    //在这儿使用了宏定义，也可以将SAVE_CFG_VARIANT用cfg.setvalue代替,具体的宏定义在上面
    SAVE_CFG_VARIANT(ip);
    SAVE_CFG_VARIANT(port);
    SAVE_CFG_VARIANT(remeberPasswd);
    cfg.sync();
}
/**初始化时显示登录信息**/
void client::loadcfg()
{
    QSettings cfg("ip_port_config.ini",QSettings::IniFormat);

    //在这儿使用了宏定义，也可以将LOAD_CFG_VARIANT用cfg.value代替
    ip= LOAD_CFG_VARIANT(ip).toString();
    port= LOAD_CFG_VARIANT(port).toString();
    //AutoLogin= LOAD_CFG_VARIANT(autologin).toString();
    RemeberPasswd= LOAD_CFG_VARIANT(remeberPasswd).toString();
    ui->ipnum->setText(ip);
    ui->portnum->setText(port);
    if(RemeberPasswd== "true")
    {
        ui->Rem_ip_port->setChecked(true);
    }

}

void client::on_appear_info_clicked()
{
    loadcfg();
}



