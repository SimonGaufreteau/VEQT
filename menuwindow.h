#ifndef MENUWINDOW_H
#define MENUWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QListWidgetItem>
#include "purplerain.h"
#include "matrixwidget.h"

namespace Ui {
class MenuWindow;
}

class MenuWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MenuWindow(QWidget *parent = nullptr);
    ~MenuWindow();

private slots:
    void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::MenuWindow *ui;
};

#endif // MENUWINDOW_H
