#include "colorimetry.h"
#include "../../arcstreamlab.h"

#include <QSlider>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

Colorimetry::Colorimetry(ActionManager *actionManager, QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Colorimetry");
    resize(200, 200);

    geometry();
    control();
    appearance();

    createColorimetryActions();

    this->actionManager = actionManager;
    this->parent = static_cast<ArcStreamLab*>(parent);

    actUndo = new QAction("undo", this);
    actUndo->setShortcut(QKeySequence("Ctrl+Z"));
    connect(actUndo, &QAction::triggered, this->parent, &ArcStreamLab::undo);

    actRedo = new QAction("redo", this);
    actRedo->setShortcut(QKeySequence("Ctrl+Y"));
    connect(actRedo, &QAction::triggered, this->parent, &ArcStreamLab::redo);

    addAction(actUndo);
    addAction(actRedo);

    defaultValues();
}

cv::Mat Colorimetry::getKernel()
{
    cv::Mat kernel = cv::Mat_<float>(3, 3);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QSlider * slider = this->slidersTab[i][j];
            kernel.at<float>(i, j) = slider->value() / 1000.0;
        }
    }

    return kernel;
}

QSlider ***Colorimetry::getSlidersTab()
{
    return this->slidersTab;
}

int Colorimetry::getWidth()
{
    return this->width;
}

int Colorimetry::getHeight()
{
    return this->height;
}

void Colorimetry::setKernel(cv::Mat kernel)
{
    for(int i = 0; i < this->width; i++)
    {
        for(int j = 0; j < this->height; j++)
        {
            this->slidersTab[i][j]->setValue(kernel.at<float>(i, j));
        }
    }
}

void Colorimetry::sloSetDefaultValues()
{
    this->actionManager->executeAction(this->caDefaultFilter);

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetRedFilter()
{
    this->actionManager->executeAction(this->caRedFilter);

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetGreenFilter()
{
    this->actionManager->executeAction(this->caGreenFilter);

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetBlueFilter()
{
    this->actionManager->executeAction(this->caBlueFilter);

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetSepiaFilter()
{
    this->actionManager->executeAction(this->caSepiaFilter);

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetBlackAndWhiteFilter()
{
    this->actionManager->executeAction(this->caBlackAndWhiteFilter);

    emit sigSlidersValueChanged();
}


void Colorimetry::geometry()
{
    this->horizontalLayoutForSliders = new QHBoxLayout(this);
    this->verticalLayout = new QVBoxLayout(this);

    this->slidersTab = new QSlider**[3];

    buttonDefaultValues = new QPushButton(this);
    buttonDefaultValues->setText(tr("Default values"));

    for (int i = 0; i < width; i++)
    {
        this->slidersTab[i] = new QSlider*[3];
        for (int j = 0; j < height; j++)
        {
            this->slidersTab[i][j] = new QSlider();
            this->horizontalLayoutForSliders->addWidget(this->slidersTab[i][j]);
        }
    }

    this->verticalLayout->addWidget(this->buttonDefaultValues);
    this->verticalLayout->addStrut(100);
    this->verticalLayout->addLayout(this->horizontalLayoutForSliders);
}

void Colorimetry::control()
{
    connect(this->buttonDefaultValues, &QPushButton::clicked, this, &Colorimetry::sloSetDefaultValues);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QSlider * slider = this->slidersTab[i][j];
            connect(slider, &QSlider::valueChanged, this, [=](){
                emit sigSlidersValueChanged();
            });
        }
    }
}

void Colorimetry::appearance()
{
    int interval = 1000;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QSlider * slider = this->slidersTab[i][j];
            slider->setTickInterval(1);
            slider->setMaximum(interval);
            slider->setMinimum(-interval);
            slider->setMaximumHeight(100);
        }
    }
}

void Colorimetry::createColorimetryActions()
{
    int **sepiaValues = new int*[3];
    for(int i=0; i<3; i++)
    {
        sepiaValues[i] = new int[3];
    }

    // sepia values
    sepiaValues[0][0] = 272;
    sepiaValues[0][1] = 534;
    sepiaValues[0][2] = 131;
    sepiaValues[1][0] = 349;
    sepiaValues[1][1] = 686;
    sepiaValues[1][2] = 168;
    sepiaValues[2][0] = 393;
    sepiaValues[2][1] = 769;
    sepiaValues[2][2] = 189;

    this->caSepiaFilter = new ColorimetryActions(sepiaValues, this->slidersTab);

    int **defaultValues = new int*[3];
    for(int i=0; i<3; i++)
    {
        defaultValues[i] = new int[3];
    }

    // default values
    defaultValues[0][0] = 1000;
    defaultValues[0][1] = 0;
    defaultValues[0][2] = 0;
    defaultValues[1][0] = 0;
    defaultValues[1][1] = 1000;
    defaultValues[1][2] = 0;
    defaultValues[2][0] = 0;
    defaultValues[2][1] = 0;
    defaultValues[2][2] = 1000;

    this->caDefaultFilter = new ColorimetryActions(defaultValues, this->slidersTab);

    int **redValues = new int*[3];
    for(int i=0; i<3; i++)
    {
        redValues[i] = new int[3];
    }

    // red values
    redValues[0][0] = 0;
    redValues[0][1] = 0;
    redValues[0][2] = 0;
    redValues[1][0] = 0;
    redValues[1][1] = 0;
    redValues[1][2] = 0;
    redValues[2][0] = 0;
    redValues[2][1] = 0;
    redValues[2][2] = 1000;

    this->caRedFilter = new ColorimetryActions(redValues, this->slidersTab);

    int **greenValues = new int*[3];
    for(int i=0; i<3; i++)
    {
        greenValues[i] = new int[3];
    }

    // green values
    greenValues[0][0] = 0;
    greenValues[0][1] = 0;
    greenValues[0][2] = 0;
    greenValues[1][0] = 0;
    greenValues[1][1] = 1000;
    greenValues[1][2] = 0;
    greenValues[2][0] = 0;
    greenValues[2][1] = 0;
    greenValues[2][2] = 0;

    this->caGreenFilter = new ColorimetryActions(greenValues, this->slidersTab);

    int **blueValues = new int*[3];
    for(int i=0; i<3; i++)
    {
        blueValues[i] = new int[3];
    }

    // blue values
    blueValues[0][0] = 800;
    blueValues[0][1] = 125;
    blueValues[0][2] = 333;
    blueValues[1][0] = 0;
    blueValues[1][1] = 0;
    blueValues[1][2] = 0;
    blueValues[2][0] = 0;
    blueValues[2][1] = 0;
    blueValues[2][2] = 0;

    this->caBlueFilter = new ColorimetryActions(blueValues, this->slidersTab);

    int **blackAndWhiteValues = new int*[3];
    for(int i=0; i<3; i++)
    {
        blackAndWhiteValues[i] = new int[3];
    }

    // black and white values
    blackAndWhiteValues[0][0] = 800;
    blackAndWhiteValues[0][1] = 700;
    blackAndWhiteValues[0][2] = 700;
    blackAndWhiteValues[1][0] = 700;
    blackAndWhiteValues[1][1] = 800;
    blackAndWhiteValues[1][2] = 700;
    blackAndWhiteValues[2][0] = 700;
    blackAndWhiteValues[2][1] = 700;
    blackAndWhiteValues[2][2] = 800;

    this->caBlackAndWhiteFilter = new ColorimetryActions(blackAndWhiteValues, this->slidersTab);
}

void Colorimetry::defaultValues()
{
    this->slidersTab[0][0]->setValue(1000);
    this->slidersTab[0][1]->setValue(0);
    this->slidersTab[0][2]->setValue(0);
    this->slidersTab[1][0]->setValue(0);
    this->slidersTab[1][1]->setValue(1000);
    this->slidersTab[1][2]->setValue(0);
    this->slidersTab[2][0]->setValue(0);
    this->slidersTab[2][1]->setValue(0);
    this->slidersTab[2][2]->setValue(1000);
}
