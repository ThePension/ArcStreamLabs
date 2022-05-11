#pragma once

#include "QBoxLayout"
#include "QVBoxLayout"
#include <QDialog>
#include "mirror.h"
#include "mosaicblureffect.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSlider;
class ArcStreamLab;

class SpecialEffect : public QDialog
{
    Q_OBJECT

    private:
        QVBoxLayout *verticalBox;

        QSlider * mosaicSlider;
        QPushButton * buttonNoFilter;
        QPushButton * buttonMirror;
        QPushButton * buttonMosaicBlur;
        ArcStreamLab *parent;
        QAction *actUndo, *actRedo;

        int mosaicTileSize;

        void geometry();
        void control();
        void appearance();

    public:
        SpecialEffect(QWidget *parent = 0);

    signals:
        void sigSetNoSpecialEffects();
        void sigSetMirrorEffect(SpecialEffectActions *);
        void sigSetMosaicBlurEffect(SpecialEffectActions *);
        void sigMosaicTileSizeChanged(int);

    private slots:
        void sloButtonNoFilter();
        void sloMirrorEffect();
        void sloMosaicBlurEffect();
        void sloMosaicSlider();
};

