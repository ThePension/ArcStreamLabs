#include "filter.h"
#include <QPushButton>
#include "../../arcstreamlab.h"

Filter::Filter(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Filter");
    resize(200, 100);

    geometry();
    control();
    appearance();

    this->parent = static_cast<ArcStreamLab*>(parent);

    actUndo = new QAction("undo", this);
    actUndo->setShortcut(QKeySequence("Ctrl+Z"));
    connect(actUndo, &QAction::triggered, this->parent, &ArcStreamLab::undo);

    actRedo = new QAction("redo", this);
    actRedo->setShortcut(QKeySequence("Ctrl+Y"));
    connect(actRedo, &QAction::triggered, this->parent, &ArcStreamLab::redo);

    addAction(actUndo);
    addAction(actRedo);
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

void Filter::sloButtonSobelFilter()
{
    FilterActions * sobelFilter = new SobelFilter();
    emit sigSetSobelFilter(sobelFilter);
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

    this->buttonSobelFilter = new QPushButton(this);
    this->buttonSobelFilter->setText(tr("Sobel filter"));

    this->verticalBox = new QVBoxLayout();
    this->verticalBox->addWidget(this->buttonDefaultFilter);
    this->verticalBox->addWidget(this->buttonRedFilter);
    this->verticalBox->addWidget(this->buttonGreenFilter);
    this->verticalBox->addWidget(this->buttonBlueFilter);
    this->verticalBox->addWidget(this->buttonBlackAndWhiteFilter);
    this->verticalBox->addWidget(this->buttonSepiaFilter);
    this->verticalBox->addWidget(this->buttonSobelFilter);
    setLayout(this->verticalBox);
}

void Filter::control()
{
    connect(this->buttonDefaultFilter, &QPushButton::clicked, this, &Filter::sloButtonDefaultFilterClick);
    connect(this->buttonRedFilter, &QPushButton::clicked, this, &Filter::sloButtonRedFilterClick);
    connect(this->buttonGreenFilter, &QPushButton::clicked, this, &Filter::sloButtonGreenFilterClick);
    connect(this->buttonBlueFilter, &QPushButton::clicked, this, &Filter::sloButtonBlueFilterClick);
    connect(this->buttonSepiaFilter, &QPushButton::clicked, this, &Filter::sloButtonSepiaFilterClick);
    connect(this->buttonBlackAndWhiteFilter, &QPushButton::clicked, this, &Filter::sloButtonBlackAndWhiteFilterClick);
    connect(this->buttonSobelFilter, &QPushButton::clicked, this, &Filter::sloButtonSobelFilter);
}

void Filter::appearance()
{

}
