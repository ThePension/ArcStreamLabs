#ifndef SETTINGS_H
#define SETTINGS_H

#include "opencv2/opencv.hpp"

#include "dialog/colorimetry/colorimetry.h"
#include "dialog/filter/filter.h"
#include "dialog/specialEffect/specialeffect.h"
#include "dialog/animation/animation.h"

#include <QObject>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <QSlider>

using namespace cv;

class Settings : public QWidget
{
    Q_OBJECT

private:
    // Dialog reference
    Colorimetry * colorDialog;
    Filter * filterDialog;
    SpecialEffect * specialEffectDialog;
    Animation * animationDialog;

    QString filename;

    void readFile();

public:
    Settings(Colorimetry *, Filter *, SpecialEffect *, Animation *, QWidget * parent = nullptr);

public slots:
    void exportSettings();
    void exportSettingsAs();
    void importSettings();
};

#endif // SETTINGS_H
