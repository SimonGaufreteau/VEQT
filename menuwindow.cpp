#include "menuwindow.h"
#include "ui_menuwindow.h"


MenuWindow::MenuWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MenuWindow)
{
    ui->setupUi(this);
}

MenuWindow::~MenuWindow()
{
    delete ui;
}

void MenuWindow::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QMainWindow* w = new QMainWindow();
    w->setMinimumSize(800,600);
    QWidget* mainWidget;
    if(item->text()=="Purple Rain")
    {
        mainWidget = new PurpleRain(w);
    }
    else if(item->text()=="Matrix"){
        mainWidget = new MatrixWidget(w);
    }
    else if(item->text()=="Boids"){
        mainWidget = new BoidsWidget(w);
    }
    else{
        delete(w);
        return;
    }
    w->setCentralWidget(mainWidget);
    w->setWindowTitle(item->text());
    w->setWindowIcon(item->icon());
    w->show();
}
