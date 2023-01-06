#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QTimer>
#include <QDateTime>


#define STATUS_INTERVAL_MS         1000
#define IMAGE_NAME_SIZE            4

bool IsSingleShotQtimerActive       = false;

const char *status_name[statusMaxIndex] = {"Nieaktywny", "Aktywny", "Nie przeszkadzac"};
const char *image_name[IMAGE_NAME_SIZE] = {"0. ", "1. ", "2. ", "3. "};

// TODO: dodaj okienko wyswietlajace wiadomosci przychodzace (obrazek i teskt)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Ustaw dane nadawcy
    sender = new User();
    sender->SetStatus(statusInactive);

    // Ustaw dane odbiorcy
    receiver = new User();
    sender->SetStatus(statusInactive);

    udpSocket = new QUdpSocket(this);

    udpSocket->bind(QHostAddress::AnyIPv4,
                    7765,
                    QUdpSocket::ShareAddress);


/* Konfiguracja Status Box uzytkownika */
    if(ui->comboBox_userStatusBox)
    {
        for(int i = 0; i < statusMaxIndex; i++) {
            ui->comboBox_userStatusBox->addItem(status_name[i]);
        }
    }

    connect(ui->comboBox_userStatusBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(senderStatusBoxChanged(int)));
/* KONIEC Konfiguracja Status Box uzytkownika */

/* Konfiguracja Image Box uzytkownika */
    if(ui->comboBox_imageBox)
    {
        for(int i = 0; i < IMAGE_NAME_SIZE; i++) {
            ui->comboBox_imageBox->addItem(image_name[i]);
        }
    }
/* KONIEC Konfiguracja Image Box uzytkownika */

    // Konfiguracja wysylania interwalowego STATUSU UZYTKOWNIKA
    QTimer::singleShot(STATUS_INTERVAL_MS, this, SLOT(sendUserStatus()));
}

MainWindow::~MainWindow()
{

    delete udpSocket;

    delete sender;
    delete receiver;

    delete ui;
}

void MainWindow::processPendingDatagrams(void)
{
    std::cout << "Cos odebralem CHYBA" << std::endl;
}


void MainWindow::senderStatusBoxChanged(int status) {

    Q_ASSERT(status >= 0 && (status < statusMaxIndex));

    sender->SetStatus((UserStatus_e)status);

    std::cout << "USER STATUS: new status: " << status << " = " << status_name[status] << std::endl;
}

void MainWindow::on_pushButton_setReceiver_clicked()
{
    QString address;
    address.clear();

    address = ui->lineEdit_reveiverAddress->text();
    receiver->SetAddress(address);

    ui->label_activeReceiver->setText(address);

    std::cout << "Set Receiver address to: " << address.toStdString() << std::endl;
}

void MainWindow::sendUserStatus(void) {

    PacketMsgStatus_s output;
    memset(&output, 0, sizeof(PacketMsgStatus_s));

    output.header.msgType       = msgType_Status;
    output.header.addressRx     = 1;
    output.header.addressTx     = 1;
    output.header.timeUTC       = QDateTime::currentSecsSinceEpoch();
    output.header.packetSize    = sizeof(PacketMsgStatus_s);
    output.header.reserved      = 0;

    output.status.status        = sender->GetStatus();

    std::cout << "Sending User Status to Receiver: " << status_name[(int)sender->GetStatus()] << std::endl;

    // TODO: dodaj wysylanie statusu uzytkownika

    QTimer::singleShot(STATUS_INTERVAL_MS, this, SLOT(sendUserStatus()));
}

void MainWindow::on_pushButton_sendMessage_clicked()
{

    if(sender->isInactive())
    {
        std::cout << "Not sending text message. STATUS INACTIVE!"<< std::endl;
        return;
    }

    QString textMessage;
    textMessage = ui->lineEdit_message->text();

    QString receiverAddr = receiver->GetAddress();
    if(receiverAddr.isEmpty())
    {
        std::cout << "Nieprawidlowy adres odbiorcy, nie wysylam!" << std::endl;
        return;
    }

    if(textMessage.isEmpty())
    {
        std::cout << "Pusta wiadomosc, nie wysylam!" << std::endl;
        return;
    }

    PacketMsgText_s output;
    memset(&output, 0, sizeof(PacketMsgText_s));

    output.header.msgType       = msgType_Text;
    output.header.addressRx     = 1;
    output.header.addressTx     = 1;
    output.header.timeUTC       = QDateTime::currentSecsSinceEpoch();
    output.header.packetSize    = sizeof(PacketMsgText_s);
    output.header.reserved      = 0;

    int len = (textMessage.length() < c_MaxTextMsgLen) ? textMessage.length() : c_MaxTextMsgLen;

    output.msg.len = len;


    for(int i = 0; i < len; i++)
    {
        output.msg.msg[i] = static_cast<char>(textMessage.toLatin1().at(i));
    }


    // TODO: dodaj wysylanie wiadomosci tekstowej zawartej w textMessage
    QHostAddress host;
    host.setAddress(receiver->GetAddress());


    qint64 sizeDatagram = 0;

    if(udpSocket)
    {
        sizeDatagram = udpSocket->writeDatagram((char *)&output,
                                                sizeof(PacketMsgText_s),
                                                host,
                                                7555);
    }

    if(sizeDatagram == sizeof(PacketMsgText_s))
    {
        std::cout << "Wyslano poprawnie!" << std::endl;
    }
    else
    {
        std::cout << "Blad wysylania!" << std::endl;
    }
    std::cout << "Wysylam wiadomosc o tresci: " << textMessage.toStdString() << std::endl;
//    std::cout << "Wysylam wiadomosc o tresci out:  " << output.msg.msg << std::endl;
}


void MainWindow::on_pushButton_sendImage_clicked()
{
    if(sender->isInactive())
    {
        std::cout << "Not sending image message. STATUS INACTIVE!"<< std::endl;
        return;
    }

    int image = 0;
    image = ui->comboBox_imageBox->currentIndex();

    QString receiverAddr = receiver->GetAddress();
    if(receiverAddr.isEmpty())
    {
        std::cout << "Nieprawidlowy adres odbiorcy, nie wysylam!" << std::endl;
        return;
    }

    PacketMsgImg_s output;
    memset(&output, 0, sizeof(PacketMsgImg_s));

    output.header.msgType       = msgType_Picture;
    output.header.addressRx     = 1;
    output.header.addressTx     = 1;
    output.header.timeUTC       = QDateTime::currentSecsSinceEpoch();
    output.header.packetSize    = sizeof(PacketMsgImg_s);
    output.header.reserved      = 0;

    output.image.picture        = image;

    std::cout << "Wysylam wiadomosc o nr obrazka: " << image << std::endl;

}

