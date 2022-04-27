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

void Filter::sloButtonDefaultFilterClick()
{
    emit sigSetDefaultFilter();
}

void Filter::sloButtonRedFilterClick()
{
    emit sigSetRedFilter();
}

void Filter::sloButtonGreenFilterClick()
{
    emit sigSetGreenFilter();
}

void Filter::sloButtonBlueFilterClick()
{
    emit sigSetBlueFilter();
}

void Filter::sloButtonSepiaFilterClick()
{
    emit sigSetSepiaFilter();
}

void Filter::sloButtonBlackAndWhiteFilterClick()
{
    emit sigSetBlackAndWhiteFilter();
}

void Filter::geometry()
{
    this->buttonDefaultFilter = new QPushButton(this);
    this->buttonDefaultFilter->setText(tr("No filters"));

    this->buttonRedFilter = new QPushButton(this);
    this->buttonRedFilter->setText(tr("Red filters"));

    this->buttonGreenFilter = new QPushButton(this);
    this->buttonGreenFilter->setText(tr("Green filters"));

    this->buttonBlueFilter = new QPushButton(this);
    this->buttonBlueFilter->setText(tr("Blue filters"));

    this->buttonSepiaFilter = new QPushButton(this);
    this->buttonSepiaFilter->setText(tr("Sepia filter"));

    this->buttonBlackAndWhiteFilter = new QPushButton(this);
    this->buttonBlackAndWhiteFilter->setText(tr("Black and White filter"));

    verticalBox = new QVBoxLayout();
    verticalBox->addWidget(buttonDefaultFilter);
    verticalBox->addWidget(buttonRedFilter);
    verticalBox->addWidget(buttonGreenFilter);
    verticalBox->addWidget(buttonBlueFilter);
    verticalBox->addWidget(buttonBlackAndWhiteFilter);
    verticalBox->addWidget(buttonSepiaFilter);
    setLayout(verticalBox);
}

void Filter::control()
{
    connect(this->buttonDefaultFilter, &QPushButton::clicked, this, &Filter::sloButtonDefaultFilterClick);
    connect(this->buttonRedFilter, &QPushButton::clicked, this, &Filter::sloButtonRedFilterClick);
    connect(this->buttonGreenFilter, &QPushButton::clicked, this, &Filter::sloButtonGreenFilterClick);
    connect(this->buttonBlueFilter, &QPushButton::clicked, this, &Filter::sloButtonBlueFilterClick);
    connect(this->buttonSepiaFilter, &QPushButton::clicked, this, &Filter::sloButtonSepiaFilterClick);
    connect(this->buttonBlackAndWhiteFilter, &QPushButton::clicked, this, &Filter::sloButtonBlackAndWhiteFilterClick);
}

void Filter::appearance()
{

}
