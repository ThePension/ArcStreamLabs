#pragma once

#include <QDialog>
#include "QBoxLayout"
#include "QVBoxLayout"
#include "sobelfilter.h"
#include "stylizationfilter.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class ArcStreamLab;

class Filter : public QDialog
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
        QPushButton * buttonSobelFilter; // Edge detector
        QPushButton * buttonStylizationFilter;
        ArcStreamLab *parent;
        QAction *actUndo, *actRedo;

        void geometry();
        void control();
        void appearance();

    public:
        Filter(QWidget *parent = 0);

    signals:
        void sigSetDefaultFilter();
        void sigSetRedFilter();
        void sigSetGreenFilter();
        void sigSetBlueFilter();
        void sigSetSepiaFilter();
        void sigSetBlackAndWhiteFilter();
        void sigSetSobelFilter(FilterActions *);
        void sigSetStylizationFilter(FilterActions *);

    private slots:
        void sloButtonDefaultFilterClick();
        void sloButtonRedFilterClick();
        void sloButtonGreenFilterClick();
        void sloButtonBlueFilterClick();
        void sloButtonSepiaFilterClick();
        void sloButtonBlackAndWhiteFilterClick();
        void sloButtonSobelFilter();
        void sloButtonStylizationFilter();
};
