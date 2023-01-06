#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

#include <QTimer>

#define STATUS_INTERVAL_MS         1000

const char *status_name[statusMaxIndex] = {"Nieaktywny", "Aktywny", "Nie przeszkadzac"};


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


    QTimer::singleShot(STATUS_INTERVAL_MS, this, SLOT(sendUserStatus()));
}

MainWindow::~MainWindow()
{

//    delete userStatus;

    delete sender;
    delete receiver;

    delete ui;
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

    // TODO: dodaj wysylanie statusu uzytkownika

    std::cout << "Sending User Status to Receiver: " << status_name[(int)sender->GetStatus()] << std::endl;


    QTimer::singleShot(STATUS_INTERVAL_MS, this, SLOT(sendUserStatus()));
}
