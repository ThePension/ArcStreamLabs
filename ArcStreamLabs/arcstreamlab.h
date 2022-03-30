#pragma once

#include <QtWidgets>

#include "colorimetry.h"
#include "filter.h"
#include "specialeffect.h"
#include "animation.h"

class ArcStreamLab : public QWidget
{
    Q_OBJECT

    private:
        QHBoxLayout *buttonsHLayout, *displayHLayout, *settingsHLayout;
        QVBoxLayout *videoInputVLayout, *mainVLayout;
        QGraphicsView *graphicViewInput, *graphicViewProcess;
        QPushButton *btnPlay, *btnPause, *btnStop, *btnSnapshot;
        QPushButton *btnColor, *btnFilter, *btnSpecialEffect, *btnAnimation;

        const float GV_WIDTH = 16;
        const float GV_HEIGHT = 9;

    public:
        ArcStreamLab(QWidget *parent=nullptr);

    private:
        void createUIGeometry();
        void createUIAppearance();
        void createUIControl();
        void imageButtons();
};
