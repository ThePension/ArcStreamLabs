#include "specialeffect.h"

SpecialEffect::SpecialEffect(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Special Effect");
    resize(200, 100);
    this->setStyleSheet("background : url(:/img/back6.png)");
}
