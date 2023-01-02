#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    userStatus = new UserStatus(ui->comboBox_userStatusBox);

    connect(ui->comboBox_userStatusBox, SIGNAL(currentIndexChanged(int)),
            this, SLOT(statusBoxChanged(int)));

}

MainWindow::~MainWindow()
{

    delete userStatus;


    delete ui;
}

void MainWindow::statusBoxChanged(int index) {
    Q_ASSERT(userStatus);
    userStatus->Update(index);
}
