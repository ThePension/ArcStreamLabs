#include "colorimetryfilter.h"
#include <QPushButton>
#include "../../arcstreamlab.h"

ColorimetryFilter::ColorimetryFilter(QWidget *parent) : QWidget(parent)
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

void ColorimetryFilter::sloButtonDefaultFilterClick()
{
    emit sigSetDefaultFilter();
}

void ColorimetryFilter::sloButtonRedFilterClick()
{
    emit sigSetRedFilter();
}

void ColorimetryFilter::sloButtonGreenFilterClick()
{
    emit sigSetGreenFilter();
}

void ColorimetryFilter::sloButtonBlueFilterClick()
{
    emit sigSetBlueFilter();
}

void ColorimetryFilter::sloButtonSepiaFilterClick()
{
    emit sigSetSepiaFilter();
}

void ColorimetryFilter::sloButtonBlackAndWhiteFilterClick()
{
    emit sigSetBlackAndWhiteFilter();
}

void ColorimetryFilter::geometry()
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

    this->verticalBox = new QVBoxLayout();
    this->verticalBox->addWidget(this->buttonDefaultFilter);
    this->verticalBox->addWidget(this->buttonRedFilter);
    this->verticalBox->addWidget(this->buttonGreenFilter);
    this->verticalBox->addWidget(this->buttonBlueFilter);
    this->verticalBox->addWidget(this->buttonBlackAndWhiteFilter);
    this->verticalBox->addWidget(this->buttonSepiaFilter);
    setLayout(this->verticalBox);
}

void ColorimetryFilter::control()
{
    connect(this->buttonDefaultFilter, &QPushButton::clicked, this, &ColorimetryFilter::sloButtonDefaultFilterClick);
    connect(this->buttonRedFilter, &QPushButton::clicked, this, &ColorimetryFilter::sloButtonRedFilterClick);
    connect(this->buttonGreenFilter, &QPushButton::clicked, this, &ColorimetryFilter::sloButtonGreenFilterClick);
    connect(this->buttonBlueFilter, &QPushButton::clicked, this, &ColorimetryFilter::sloButtonBlueFilterClick);
    connect(this->buttonSepiaFilter, &QPushButton::clicked, this, &ColorimetryFilter::sloButtonSepiaFilterClick);
    connect(this->buttonBlackAndWhiteFilter, &QPushButton::clicked, this, &ColorimetryFilter::sloButtonBlackAndWhiteFilterClick);
}

void ColorimetryFilter::appearance()
{

}
