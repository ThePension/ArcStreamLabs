#pragma once

#include <QDialog>
#include <QVBoxLayout>
#include <QTabWidget>

#include "colorimetry.h"
#include "colorimetryfilter.h"

class ColorimetryTabs : public QDialog
{
    Q_OBJECT

    private:
        QTabWidget *tabWidget;

    public:
        ColorimetryTabs(Colorimetry * colorimetry, ColorimetryFilter * colorimetryFilter, QWidget *parent = 0);
        ~ColorimetryTabs() {};
};
