#pragma once

#include "QBoxLayout"
#include "QVBoxLayout"
#include <QDialog>
#include "mirror.h"

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

    private slots:
        void sloButtonNoFilter();
        void sloMirrorEffect();
};

