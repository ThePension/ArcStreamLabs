#pragma once

#include <QDialog>
#include <QTabWidget>

#include "colorimetry.h"

class ColorimetryTabs : public QDialog
{
    Q_OBJECT

    private:
        QTabWidget *tabWidget;

    public:
        ColorimetryTabs(Colorimetry * colorimetry, QWidget *parent = 0);
        ~ColorimetryTabs() {};
};
