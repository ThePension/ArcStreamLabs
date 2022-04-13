#include "filter.h"
#include <QPushButton>

Filter::Filter(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Filter");
    resize(200, 100);

    geometry();
    control();
    appearance();
}

void Filter::sloButtonSepiaFilterClick()
{
    emit sigSetSepiaFilter();
}

void Filter::geometry()
{
    this->buttonSepiaFilter = new QPushButton(this);
    this->buttonSepiaFilter->setText(tr("Sepia filter"));
}

void Filter::control()
{
    connect(this->buttonSepiaFilter, &QPushButton::clicked, this, &Filter::sloButtonSepiaFilterClick);
}

void Filter::appearance()
{

}
