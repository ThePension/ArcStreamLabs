#pragma once

#include <QDialog>

#include "mustacheanimation.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QVBoxLayout;
class ArcStreamLab;

class Animation : public QDialog
{
    Q_OBJECT

    private:
        QVBoxLayout *verticalBox;

        QPushButton * buttonMustacheAnimation;

        ArcStreamLab *parent;
        QAction *actUndo, *actRedo;

        void geometry();
        void control();
        void appearance();

    public:
        Animation(QWidget *parent = 0);

    signals:
        void sigSetMustacheAnimation(AnimationActions *);

    private slots:
        void sloButtonMustacheAnimation();
};
