#pragma once

#include "QBoxLayout"
#include "QVBoxLayout"
#include <QDialog>
#include "mirror.h"
#include "mosaicblureffect.h"
#include "facialblureffect.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSlider;
class ArcStreamLab;
class QRadioButton;
class QGroupBox;

class SpecialEffect : public QDialog
{
    Q_OBJECT

    private:
        QVBoxLayout *verticalBox;

        QGroupBox *superpositionGroupBox;
        QRadioButton *radioSuperpositionNo;
        QRadioButton *radioSuperpositionYes;

        QSlider * mosaicSlider;
        QPushButton * buttonNoFilter;
        QPushButton * buttonMirror;
        QPushButton * buttonMosaicBlur;
        QPushButton * buttonFacialBlur;
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
        void sigSetFacialBlurEffect(SpecialEffectActions *);

    private slots:
        void sloButtonNoFilter();
        void sloMirrorEffect();
        void sloMosaicBlurEffect();
        void sloMosaicSlider();
        void sloFacialBlurEffect();
};

