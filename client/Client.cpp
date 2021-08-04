#include "Client.h"
#include "ui_client.h"

Client::Client(QWidget* parent) :
    QWidget(parent)
{
    ui.setupUi(this);
    this->setWindowTitle("Client");
    socket = new QTcpSocket;
    socketState = false;

    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnectedSignal()));     //客户端断开连接
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyReadSignal()));           //接收消息
}
void Client::on_Connect_clicked()
{
    QString ipAddressStr = ui.lineEditAddress->text();
    quint16 port = ui.lineEditPort->text().toInt();

    if (!socketState)
    {
        socket->connectToHost(ipAddressStr, port);
        if (socket->waitForConnected(3000))
        {
            ui.pushButtonConnect->setText(QString::fromLocal8Bit("断开连接"));
            socketState = true;
            ui.textBrowserRecv->append(QString::fromLocal8Bit("连接成功"));
        }
    }
    else
    {
        socket->close();//触发disconnected()信号
        ui.pushButtonConnect->setText(QString::fromLocal8Bit("连接"));

        socketState = false;
    }
}

void Client::disconnectedSignal()
{
    ui.textBrowserRecv->append(QString::fromLocal8Bit("已退出聊天室"));
}

void Client::readyReadSignal()
{
    QByteArray dataBa = socket->readAll();
    QString str = QString(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"))+"[Server]:Recv\n" + str.fromLocal8Bit(dataBa.data()); 
    ui.textBrowserRecv->append(QString(str));
}

void Client::on_Send_clicked()
{
    QString dataStr = ui.textEditSend->toPlainText();
    QByteArray data = dataStr.toLocal8Bit();    
    if (socket->isOpen() && socket->isValid())
    {
        socket->write(data);
    }
    QString str = QString(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss")) +"[Me]\n" + str.fromLocal8Bit(data.data()); 
    ui.textBrowserRecv->append(QString(str));
}

