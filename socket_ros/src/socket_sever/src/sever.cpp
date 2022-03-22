#include<ros/ros.h>
#include<std_msgs/String.h>
#include<unistd.h>
#include<stdio.h>
#include<x86_64-linux-gnu/sys/socket.h>
#include<netinet/in.h>
#include<x86_64-linux-gnu/sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
int main(int argc, char  *argv[])
{
    setlocale(LC_ALL,"");
//1. 初始化ros
    ros::init(argc,argv,"socket_ros");
    ros::NodeHandle n;
//2. 建立socket连接
    //创建套接字
    int serv_sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //将套接字和IP、端口绑定
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));  //每个字节都用0填充
    serv_addr.sin_family = AF_INET;  //使用IPv4地址
    serv_addr.sin_addr.s_addr = inet_addr("192.168.133.2");  //具体的IP地址
    serv_addr.sin_port = htons(1234);  //端口
    bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    //进入监听状态，等待用户发起请求
    listen(serv_sock, 20);
    //接收客户端请求
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    char  buffer [BUFSIZ]={0};  //缓冲区
    ROS_INFO("服务器已启动，正在监听...");
    while(1){
    int clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    int strlen =read(clnt_sock,buffer,BUFSIZ);
    //向客户端发送数据
    if (sizeof(buffer)!=0)
    {
      write(clnt_sock, buffer, sizeof(buffer));
     ROS_INFO("Success send:%s",buffer);
    }
    
    
    //关闭套接字
    close(clnt_sock);
    memset(buffer,0,BUFSIZ);
    }
   
    close(serv_sock);
    return 0;
}
