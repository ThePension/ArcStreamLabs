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

void Filter::sloButtonNoFilter()
{
    emit sigSetNoFilter();
}

void Filter::sloButtonSobelFilter()
{
    if(radioSuperpositionNo->isChecked())
        emit sigSetNoFilter();
    FilterActions * sobelFilter = new SobelFilter();
    emit sigSetSobelFilter(sobelFilter);
}

void Filter::sloButtonStylizationFilter()
{
    if(radioSuperpositionNo->isChecked())
        emit sigSetNoFilter();
    FilterActions * stylizationFilter = new StylizationFilter();
    emit sigSetSobelFilter(stylizationFilter);
}

void Filter::sloButtonLongExposureFilter()
{
    if(radioSuperpositionNo->isChecked())
        emit sigSetNoFilter();
    FilterActions * longExposureFilter = new LongExposure();
    emit sigSetSobelFilter(longExposureFilter);
}

void Filter::geometry()
{
    this->superpositionGroupBox = new QGroupBox("Superposition des effets ?");
    this->radioSuperpositionNo = new QRadioButton("Non", this);
    this->radioSuperpositionYes = new QRadioButton("Oui", this);
    radioSuperpositionNo->setChecked(true);

    QHBoxLayout *hbox = new QHBoxLayout;
    hbox->addWidget(radioSuperpositionNo);
    hbox->addWidget(radioSuperpositionYes);
    superpositionGroupBox->setLayout(hbox);

    this->buttonNoFilter = new QPushButton(this);
    this->buttonNoFilter->setText(tr("No filter"));

    this->buttonSobelFilter = new QPushButton(this);
    this->buttonSobelFilter->setText(tr("Sobel filter"));

    this->buttonLongExposureFilter = new QPushButton(this);
    this->buttonLongExposureFilter->setText(tr("Exposure filter"));


    this->buttonStylizationFilter = new QPushButton(this);
    this->buttonStylizationFilter->setText(tr("Stylization filter"));

    this->verticalBox = new QVBoxLayout();
    this->verticalBox->addWidget(superpositionGroupBox);
    this->verticalBox->addWidget(this->buttonNoFilter);
    this->verticalBox->addWidget(this->buttonSobelFilter);
    this->verticalBox->addWidget(this->buttonLongExposureFilter);
    this->verticalBox->addWidget(this->buttonStylizationFilter);
    setLayout(this->verticalBox);
}

void Filter::control()
{
    connect(this->buttonNoFilter, &QPushButton::clicked, this, &Filter::sloButtonNoFilter);
    connect(this->buttonSobelFilter, &QPushButton::clicked, this, &Filter::sloButtonSobelFilter);
    connect(this->buttonStylizationFilter, &QPushButton::clicked, this, &Filter::sloButtonStylizationFilter);
    connect(this->buttonLongExposureFilter, &QPushButton::clicked, this, &Filter::sloButtonLongExposureFilter);
}

void Filter::appearance()
{
    int minHeight = 40, maxHeight = 80;

    QString btnRadio =
            "QRadioButton{"
                "color: white;"
                "background-color: rgba(120, 120, 120, 0);"
                "border:0px solid rgb(0,0,0);"
                "}";

    this->superpositionGroupBox->setStyleSheet("color:white");
    this->superpositionGroupBox->setMaximumHeight(maxHeight);
    this->radioSuperpositionNo->setStyleSheet(btnRadio);
    this->radioSuperpositionYes->setStyleSheet(btnRadio);

    this->buttonNoFilter->setMinimumHeight(minHeight);
    this->buttonNoFilter->setMaximumHeight(maxHeight);
    this->buttonSobelFilter->setMinimumHeight(minHeight);
    this->buttonSobelFilter->setMaximumHeight(maxHeight);
    this->buttonLongExposureFilter->setMinimumHeight(minHeight);
    this->buttonLongExposureFilter->setMaximumHeight(maxHeight);
    this->buttonStylizationFilter->setMinimumHeight(minHeight);
    this->buttonStylizationFilter->setMaximumHeight(maxHeight);

}
