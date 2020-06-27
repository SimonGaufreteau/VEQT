#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "purplerain.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    PurpleRain* rain = new PurpleRain(this);
    setCentralWidget(rain);
}

MainWindow::~MainWindow()
{
    delete ui;
}

