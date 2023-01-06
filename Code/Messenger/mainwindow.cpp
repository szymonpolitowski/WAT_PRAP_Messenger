#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    userStatus = new UserStatus(ui->comboBox_userStatusBox);

    // Ustaw dane nadawcy
    sender = new User();
    sender->SetStatus(statusInactive);

    // Ustaw dane odbiorcy
    receiver = new User();
    sender->SetStatus(statusInactive);




    connect(ui->comboBox_userStatusBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(statusBoxChanged(int)));

}

MainWindow::~MainWindow()
{

//    delete userStatus;

    delete sender;
    delete receiver;

    delete ui;
}

void MainWindow::statusBoxChanged(int index) {
//    Q_ASSERT(userStatus);
//    userStatus->Update(index);
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

