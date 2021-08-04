#pragma once

#include <QtWidgets/QWidget>
#include "ui_Client.h"
#include <QTcpSocket>
#include <QMessageBox>
#include <QDateTime>
class Client : public QWidget
{
    Q_OBJECT

public:
    Client(QWidget *parent = Q_NULLPTR);

private:
    Ui::ClientClass ui;
    QTcpSocket* socket;
    bool socketState;
private slots:
    void on_Connect_clicked();
    void disconnectedSignal();
    void readyReadSignal();
    void on_Send_clicked();

};
