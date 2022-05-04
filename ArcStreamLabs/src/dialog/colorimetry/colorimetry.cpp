#include "colorimetry.h"
#include "../../arcstreamlab.h"

#include <QSlider>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

Colorimetry::Colorimetry(ActionManager *actionManager, QWidget *parent) : QWidget(parent)
{
    this->actionManager = actionManager;
    this->parent = static_cast<ArcStreamLab*>(parent);

    this->tempBackupValues = new int*[3];
    for(int i=0; i<3; i++)
    {
        this->tempBackupValues[i] = new int[3];
    }

    geometry();
    control();
    appearance();

    redirectAction();
    defaultValues();
}

Colorimetry::~Colorimetry()
{
    for(int i=0; i<3; i++)
    {
        delete [] this->tempBackupValues[i];
    }

    delete [] this->tempBackupValues;

    delete this->horizontalLayoutForSliders;
    delete this->verticalLayout;
}

void Colorimetry::geometry()
{
    this->horizontalLayoutForSliders = new QHBoxLayout();
    this->verticalLayout = new QVBoxLayout();

    setLayout(verticalLayout);

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
    this->verticalLayout->addSpacing(20);
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
            connect(slider, &QSlider::sliderPressed, this, &Colorimetry::backupSliderValues);
            connect(slider, &QSlider::sliderReleased, this, &Colorimetry::createReleaseAction);
        }
    }
}

void Colorimetry::appearance()
{
    setWindowTitle("Colorimetry");
    this->setStyleSheet("background : url(:/img/back6.png)");
    resize(200, 200);

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

    this->actionManager->executeAction(createColorimetryAction(defaultValues));

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetRedFilter()
{
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

    this->actionManager->executeAction(createColorimetryAction(redValues));

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetGreenFilter()
{
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

    this->actionManager->executeAction(createColorimetryAction(greenValues));

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetBlueFilter()
{
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

    this->actionManager->executeAction(createColorimetryAction(blueValues));

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetSepiaFilter()
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

    this->actionManager->executeAction(createColorimetryAction(sepiaValues));

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetBlackAndWhiteFilter()
{
    int **blackAndWhiteValues = new int*[3];
    for(int i=0; i<3; i++)
    {
        blackAndWhiteValues[i] = new int[3];
    }

    // black and white values
    blackAndWhiteValues[0][0] = 300;
    blackAndWhiteValues[0][1] = 200;
    blackAndWhiteValues[0][2] = 150;
    blackAndWhiteValues[1][0] = 300;
    blackAndWhiteValues[1][1] = 200;
    blackAndWhiteValues[1][2] = 150;
    blackAndWhiteValues[2][0] = 300;
    blackAndWhiteValues[2][1] = 200;
    blackAndWhiteValues[2][2] = 150;

    this->actionManager->executeAction(createColorimetryAction(blackAndWhiteValues));

    emit sigSlidersValueChanged();
}

void Colorimetry::backupSliderValues()
{
    this->tempBackupValues[0][0] = this->slidersTab[0][0]->value();
    this->tempBackupValues[0][1] = this->slidersTab[0][1]->value();
    this->tempBackupValues[0][2] = this->slidersTab[0][2]->value();
    this->tempBackupValues[1][0] = this->slidersTab[1][0]->value();
    this->tempBackupValues[1][1] = this->slidersTab[1][1]->value();
    this->tempBackupValues[1][2] = this->slidersTab[1][2]->value();
    this->tempBackupValues[2][0] = this->slidersTab[2][0]->value();
    this->tempBackupValues[2][1] = this->slidersTab[2][1]->value();
    this->tempBackupValues[2][2] = this->slidersTab[2][2]->value();
}

void Colorimetry::createReleaseAction()
{
    int **backupValues = new int*[3];
    for(int i=0; i<3; i++)
    {
        backupValues[i] = new int[3];
    }

    backupValues[0][0] = this->tempBackupValues[0][0];
    backupValues[0][1] = this->tempBackupValues[0][1];
    backupValues[0][2] = this->tempBackupValues[0][2];
    backupValues[1][0] = this->tempBackupValues[1][0];
    backupValues[1][1] = this->tempBackupValues[1][1];
    backupValues[1][2] = this->tempBackupValues[1][2];
    backupValues[2][0] = this->tempBackupValues[2][0];
    backupValues[2][1] = this->tempBackupValues[2][1];
    backupValues[2][2] = this->tempBackupValues[2][2];

    int **newValues = new int*[3];
    for(int i=0; i<3; i++)
    {
        newValues[i] = new int[3];
    }

    newValues[0][0] = this->slidersTab[0][0]->value();
    newValues[0][1] = this->slidersTab[0][1]->value();
    newValues[0][2] = this->slidersTab[0][2]->value();
    newValues[1][0] = this->slidersTab[1][0]->value();
    newValues[1][1] = this->slidersTab[1][1]->value();
    newValues[1][2] = this->slidersTab[1][2]->value();
    newValues[2][0] = this->slidersTab[2][0]->value();
    newValues[2][1] = this->slidersTab[2][1]->value();
    newValues[2][2] = this->slidersTab[2][2]->value();

    this->actionManager->executeAction(new ColorimetryActions(backupValues, newValues, this->slidersTab));
}

ColorimetryActions* Colorimetry::createColorimetryAction(int **colorValues)
{
    return new ColorimetryActions(colorValues, this->slidersTab);
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

void Colorimetry::redirectAction()
{
    actUndo = new QAction("undo", this);
    actUndo->setShortcut(QKeySequence("Ctrl+Z"));
    connect(actUndo, &QAction::triggered, this->parent, &ArcStreamLab::undo);

    actRedo = new QAction("redo", this);
    actRedo->setShortcut(QKeySequence("Ctrl+Y"));
    connect(actRedo, &QAction::triggered, this->parent, &ArcStreamLab::redo);

    addAction(actUndo);
    addAction(actRedo);
}
