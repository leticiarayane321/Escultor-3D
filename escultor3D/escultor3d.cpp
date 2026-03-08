#include "escultor3d.h"
#include "ui_escultor3d.h"
#include "sculptor.h"

escultor3d::escultor3d(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::escultor3d)
{
    ui->setupUi(this);
}

escultor3d::~escultor3d()
{
    delete ui;
}
