#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QTcpSocket>//服务端只用socket
#include <QSettings>
#include<QString>
QT_BEGIN_NAMESPACE
namespace Ui { class client; }
QT_END_NAMESPACE

class client : public QMainWindow
{
    Q_OBJECT

public:
    client(QWidget *parent = nullptr);
    ~client();
    QTcpSocket *tcpsocket;
    QString ip;
    QString port;
    QString AUtologin;
    QString RemeberPasswd;
    bool		remeberPasswd;
    bool		autologin;
    void		savecfg();
    void		loadcfg();
private slots:
    void connected_SLOT();
    void readyRead_Slot();
    //void appendMessageToEditor(const QString &message);
    void on_closeclient_clicked();
    void on_Rem_ip_port_clicked();
    void on_sent_clicked();
    void on_appear_info_clicked();
   // void slot_disconnect();
//    void slot_sendmessage(); //发送消息到服务器的槽
//    void slot_recvmessage(); //接收来自服务器的消息的槽

    void on_connect_sever_clicked();

  private:
    Ui::client *ui;
    bool isconnetion; //判断是否连接到服务器的标志位
    QTcpSocket *TCP_sendMesSocket; //发送消息套接字
};
#endif // CLIENT_H

