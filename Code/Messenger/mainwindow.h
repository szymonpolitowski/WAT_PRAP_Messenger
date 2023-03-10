#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUdpSocket>
#include "user.h"
#include "messenger_declarations.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    User *sender;
    User *receiver;

    QUdpSocket *udpSocket;

private slots:
    void processPendingDatagrams(void);

    void senderStatusBoxChanged(int status);

    void sendUserStatus(void);

//    void setReceiverStatus(UserStatus_e status);

    void on_pushButton_setReceiver_clicked();
    void on_pushButton_sendMessage_clicked();
    void on_pushButton_sendImage_clicked();
};
#endif // MAINWINDOW_H
