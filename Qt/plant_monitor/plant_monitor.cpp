#include "plant_monitor.h"
#include "ui_plant_monitor.h"

#include <iostream>
#include <cstdio>
#include <cstring>
#include <QDebug>
plant_monitor::plant_monitor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::plant_monitor)
{
    ui->setupUi(this);
//----------------------------------------------
//初始化TCP客户端
         setup();
}

plant_monitor::~plant_monitor()
{
    delete ui;
}

//-----------------------------------------------------------------------------------
//TCP客户端相关函数
void plant_monitor::setup()
{
     tcpClient =  new QTcpSocket();//实例化tcpClient
     tcpClient -> abort();             //取消原有连接
//-----------------------------------------------
//连接TCP_Client槽函数
     connect(tcpClient, SIGNAL(readyRead()                        ), this, SLOT(ReadData()                              ));
     connect(tcpClient, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(ReadError(QAbstractSocket::SocketError) ));

//-----------------------------------------------
//连接Button槽函数
     connect(ui->connect_btn, SIGNAL(clicked()), this, SLOT(WIFI_Connect()));//按钮0
}

int flag;
void plant_monitor::WIFI_Connect()
{
//-----------------------------------------------
//连接函数,开启魔法的时候，可能会连不上，建议关掉
    if(!flag)
    {
        tcpClient->connectToHost(ui->IP_Input->text(), ui->Port_Input->text().toInt());
        ui->WIFI->setText("连接中");
        if (tcpClient->waitForConnected(1000))//连接成功则进入if{}
        {
            ui->WIFI->setText("已连接");
        }
        flag = 1;
    }
//-----------------------------------------------
//断开连接函数
    else
    {
        tcpClient->disconnectFromHost();
        if (tcpClient->state() == QAbstractSocket::UnconnectedState || tcpClient->waitForDisconnected(1000))//连接后断开则进入if{}
        {
            ui->WIFI->setText("未连接");
        }
        flag = 0;
    }

}


void plant_monitor::ReadError(QAbstractSocket::SocketError)
{
     tcpClient->disconnectFromHost();
     ui->WIFI->setText( "读取出错" );
}


int Count;
unsigned char temp[200];
unsigned char *buffer_temp;
char TXT_light      [200];
char TXT_humidity   [200];
char TXT_temperature[200];

int  num_light;
int  num_humidity;
int  num_temperature;

int  num_flag;
void plant_monitor::Handle()
{
    int A = 1;

    if (buffer_temp[0] == 'h')
    {
        std::memset(temp           ,0,sizeof(temp            ));//清除数组
        std::memset(TXT_light      ,0,sizeof(TXT_light       ));//清除数组
        std::memset(TXT_humidity   ,0,sizeof(TXT_humidity    ));//清除数组
        std::memset(TXT_temperature,0,sizeof(TXT_temperature ));//清除数组
        for(A = 1 ; A < Count; A++)
        {
            if (buffer_temp[A] == '~' && num_flag == 2)
            {
                std::memcpy(TXT_temperature,buffer_temp + 3 + std::strlen(TXT_light) + std::strlen(TXT_humidity),A - std::strlen(TXT_light) - std::strlen(TXT_humidity)-1);//把数组的字符都提取出来
                num_temperature = std::atoi((char*)TXT_temperature);
                std::sprintf((char*)TXT_temperature,"%d",num_temperature);
                ui->temperature_digit->setText((char*)TXT_temperature);
                num_flag = 0;
                break;
            }
            if (buffer_temp[A] == '~' && num_flag == 1)
            {
                std::memcpy(TXT_light,buffer_temp + 2 + std::strlen(TXT_humidity),A - std::strlen(TXT_humidity)-1);//把数组的字符都提取出来
                num_light = std::atoi((char*)TXT_light);
                ui->light_digit->setNum(num_light);
                num_flag = 2;
            }
            if (buffer_temp[A] == '~' && num_flag == 0)
            {
                std::memcpy(TXT_humidity,buffer_temp + 1,A-1);//把数组的字符都提取出来
                num_humidity = std::atoi((char*)TXT_humidity);
                std::sprintf((char*)TXT_humidity,"%d%%",num_humidity);
                ui->humidity_digit->setText((char*)TXT_humidity);
                num_flag = 1;
            }



         }
         if (A >= Count)
         {
             num_flag = 0;
         }
    }
}

void plant_monitor::ReadData()
{
     QByteArray buffer = tcpClient->readAll();//读取字节
     buffer_temp       = reinterpret_cast<unsigned char*> (buffer.data());
     Count             = std::strlen((char*)buffer_temp);

     Handle();

     if(num_light    > 50)
     {
         state_flag = 1;
         if(num_light > 50 && num_humidity < 20)state_flag =3;
     }
     else
     {
         state_flag = 0;
     }

     if(num_humidity < 20)
     {
         state_flag = 2;
         if(num_light > 50 && num_humidity < 20)state_flag =3;
     }
     else
     {
         state_flag = 0;
         if(num_light > 50)state_flag =1;
     }


     if     (state_flag == 0)ui->state->setText("生长良好");
     else if(state_flag == 1)ui->state->setText("暴晒");
     else if(state_flag == 2)ui->state->setText("缺水");
     else if(state_flag == 3)ui->state->setText("缺水,暴晒");

     if(!buffer.isEmpty())//当buffer不为空时，右方大框显示buffer内容
     {
//         ui->Read_Text->append(buffer);
     }
}
