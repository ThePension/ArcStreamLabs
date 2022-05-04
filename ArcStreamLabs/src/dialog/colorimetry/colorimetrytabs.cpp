#include "colorimetrytabs.h"

ColorimetryTabs::ColorimetryTabs(Colorimetry * colorimetry, QWidget *parent) : QDialog(parent)
{
    this->resize(400, 400);

    this->tabWidget = new QTabWidget(this);
    this->tabWidget->addTab(colorimetry, "Sliders");
    //this->tabWidget->currentWidget()->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
}
