#ifndef PLANT_MONITOR_H
#define PLANT_MONITOR_H

#include <QMainWindow>

//----------------------------
//TCP
#include <QMainWindow>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class plant_monitor; }
QT_END_NAMESPACE

class plant_monitor : public QMainWindow
{
    Q_OBJECT

public:
    plant_monitor(QWidget *parent = nullptr);
    ~plant_monitor();

private:
    Ui::plant_monitor *ui;
    QTcpSocket *tcpClient;
private slots:
    void setup();
    void WIFI_Connect();
    void ReadError(QAbstractSocket::SocketError);
    void ReadData();
    void Handle();
private:
    int state_flag;
};
#endif // PLANT_MONITOR_H
