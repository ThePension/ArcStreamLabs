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
class ArcStreamLab;

class SpecialEffect : public QDialog
{
    Q_OBJECT

    private:
        QVBoxLayout *verticalBox;

        QPushButton * buttonNoFilter;
        QPushButton * buttonMirror;
        QPushButton * buttonMosaicBlur;
        ArcStreamLab *parent;
        QAction *actUndo, *actRedo;

        void geometry();
        void control();
        void appearance();

    public:
        SpecialEffect(QWidget *parent = 0);

    signals:
        void sigSetNoFilter(SpecialEffectActions *);
        void sigSetMirrorEffect(SpecialEffectActions *);
        void sigSetMosaicBlurEffect(SpecialEffectActions *);

    private slots:
        void sloButtonNoFilter();
        void sloMirrorEffect();
        void sloMosaicBlurEffect();
};

