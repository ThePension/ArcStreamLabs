#pragma once

#include <QDialog>

#include "mustacheanimation.h"
#include "textanimation.h"

class QCheckBox;
class QLabel;
class QTextEdit;
class QPushButton;
class QLineEdit;
class QVBoxLayout;
class ArcStreamLab;

class Animation : public QDialog
{
    Q_OBJECT

    private:
        QVBoxLayout *verticalBox;

        QPushButton * buttonMustacheAnimation;
        QPushButton * buttonText;
        QLineEdit * lineEditText;

        ArcStreamLab *parent;
        QAction *actUndo, *actRedo;

        void geometry();
        void control();
        void appearance();

    public:
        Animation(QWidget *parent = 0);

    signals:
        void sigSetMustacheAnimation(AnimationActions *);
        void sigSetTextAnimation(AnimationActions *);

    private slots:
        void sloButtonMustacheAnimation();
        void sloButtonTextAnimation();
};
