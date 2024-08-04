#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btn_addPoint, &QPushButton::clicked,
            this, &MainWindow::hello);
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::hello()
{
    qDebug() << "zhopa" << endl;
}

