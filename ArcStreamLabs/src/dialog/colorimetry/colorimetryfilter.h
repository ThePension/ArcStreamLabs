#pragma once

#include <QWidget>

#include "QBoxLayout"
#include "QVBoxLayout"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class ArcStreamLab;

class ColorimetryFilter : public QWidget
{
    Q_OBJECT

    private:
        QVBoxLayout *verticalBox;

        QPushButton * buttonDefaultFilter;
        QPushButton * buttonRedFilter;
        QPushButton * buttonGreenFilter;
        QPushButton * buttonBlueFilter;
        QPushButton * buttonSepiaFilter;
        QPushButton * buttonBlackAndWhiteFilter;

        ArcStreamLab *parent;
        QAction *actUndo, *actRedo;

        void geometry();
        void control();
        void appearance();

    public:
        ColorimetryFilter(QWidget *parent = 0);

    signals:
        void sigSetDefaultFilter();
        void sigSetRedFilter();
        void sigSetGreenFilter();
        void sigSetBlueFilter();
        void sigSetSepiaFilter();
        void sigSetBlackAndWhiteFilter();

    private slots:
        void sloButtonDefaultFilterClick();
        void sloButtonRedFilterClick();
        void sloButtonGreenFilterClick();
        void sloButtonBlueFilterClick();
        void sloButtonSepiaFilterClick();
        void sloButtonBlackAndWhiteFilterClick();
};
