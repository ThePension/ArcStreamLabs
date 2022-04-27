#include "colorimetry.h"
#include <QSlider>
#include <QHBoxLayout>
#include <QPushButton>
#include <QVBoxLayout>

Colorimetry::Colorimetry(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Colorimetry");
    resize(200, 200);

    geometry();
    control();
    appearance();

    sloSetDefaultValues();
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

void Colorimetry::sloSetDefaultValues()
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

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetRedFilter()
{
    this->slidersTab[0][0]->setValue(0);
    this->slidersTab[0][1]->setValue(0);
    this->slidersTab[0][2]->setValue(0);
    this->slidersTab[1][0]->setValue(0);
    this->slidersTab[1][1]->setValue(0);
    this->slidersTab[1][2]->setValue(0);
    this->slidersTab[2][0]->setValue(0);
    this->slidersTab[2][1]->setValue(0);
    this->slidersTab[2][2]->setValue(1000);

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetGreenFilter()
{
    this->slidersTab[0][0]->setValue(0);
    this->slidersTab[0][1]->setValue(0);
    this->slidersTab[0][2]->setValue(0);
    this->slidersTab[1][0]->setValue(0);
    this->slidersTab[1][1]->setValue(1000);
    this->slidersTab[1][2]->setValue(0);
    this->slidersTab[2][0]->setValue(0);
    this->slidersTab[2][1]->setValue(0);
    this->slidersTab[2][2]->setValue(0);

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetBlueFilter()
{
    this->slidersTab[0][0]->setValue(800);
    this->slidersTab[0][1]->setValue(125);
    this->slidersTab[0][2]->setValue(333);
    this->slidersTab[1][0]->setValue(0);
    this->slidersTab[1][1]->setValue(0);
    this->slidersTab[1][2]->setValue(0);
    this->slidersTab[2][0]->setValue(0);
    this->slidersTab[2][1]->setValue(0);
    this->slidersTab[2][2]->setValue(0);

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetSepiaFilter()
{
    this->slidersTab[0][0]->setValue(272);
    this->slidersTab[0][1]->setValue(534);
    this->slidersTab[0][2]->setValue(131);
    this->slidersTab[1][0]->setValue(349);
    this->slidersTab[1][1]->setValue(686);
    this->slidersTab[1][2]->setValue(168);
    this->slidersTab[2][0]->setValue(393);
    this->slidersTab[2][1]->setValue(769);
    this->slidersTab[2][2]->setValue(189);

    emit sigSlidersValueChanged();
}

void Colorimetry::sloSetBlackAndWhiteFilter()
{
    this->slidersTab[0][0]->setValue(800);
    this->slidersTab[0][1]->setValue(700);
    this->slidersTab[0][2]->setValue(700);
    this->slidersTab[1][0]->setValue(700);
    this->slidersTab[1][1]->setValue(800);
    this->slidersTab[1][2]->setValue(700);
    this->slidersTab[2][0]->setValue(700);
    this->slidersTab[2][1]->setValue(700);
    this->slidersTab[2][2]->setValue(800);

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
