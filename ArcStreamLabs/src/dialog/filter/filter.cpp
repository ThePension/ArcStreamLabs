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

void Filter::sloButtonSobelFilter()
{
    FilterActions * sobelFilter = new SobelFilter();
    emit sigSetSobelFilter(sobelFilter);
}

void Filter::sloButtonStylizationFilter()
{
    FilterActions * stylizationFilter = new StylizationFilter();
    emit sigSetSobelFilter(stylizationFilter);
}

void Filter::geometry()
{
    this->buttonSobelFilter = new QPushButton(this);
    this->buttonSobelFilter->setText(tr("Sobel filter"));

    this->buttonStylizationFilter = new QPushButton(this);
    this->buttonStylizationFilter->setText(tr("Stylization filter"));

    this->verticalBox = new QVBoxLayout();
    this->verticalBox->addWidget(this->buttonSobelFilter);
    this->verticalBox->addWidget(this->buttonStylizationFilter);
    setLayout(this->verticalBox);
}

void Filter::control()
{
    connect(this->buttonSobelFilter, &QPushButton::clicked, this, &Filter::sloButtonSobelFilter);
    connect(this->buttonStylizationFilter, &QPushButton::clicked, this, &Filter::sloButtonStylizationFilter);
}

void Filter::appearance()
{
    this->setStyleSheet("background : url(:/img/back6.png)");
}
