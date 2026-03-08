#ifndef ESCULTOR3D_H
#define ESCULTOR3D_H
#include "figurageometrica.h"
#include "sculptor.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class escultor3d;
}
QT_END_NAMESPACE

class escultor3d : public QMainWindow
{
    Q_OBJECT

public:
    escultor3d(QWidget *parent = nullptr);
    ~escultor3d();

private:
    Ui::escultor3d *ui;
};
#endif // ESCULTOR3D_H
