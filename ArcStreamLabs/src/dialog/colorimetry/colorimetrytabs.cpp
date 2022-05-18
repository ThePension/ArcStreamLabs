#include "colorimetrytabs.h"

ColorimetryTabs::ColorimetryTabs(Colorimetry * colorimetry, ColorimetryFilter * colorimetryFilter, QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    this->tabWidget = new QTabWidget(this);
    this->tabWidget->addTab(colorimetry, "Sliders");
    this->tabWidget->addTab(colorimetryFilter, "pre-made filters");

    mainLayout->addWidget(this->tabWidget);
    this->setStyleSheet("background : url(:/img/popupBack.jpg)");
}
