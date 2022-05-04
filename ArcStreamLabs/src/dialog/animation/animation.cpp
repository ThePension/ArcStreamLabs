#include "animation.h"

Animation::Animation(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Animation");
    resize(200, 100);
    this->setStyleSheet("background : url(:/img/back6.png)");
}
