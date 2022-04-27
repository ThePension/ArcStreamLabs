#pragma once

#include <QDialog>
#include "opencv2/opencv.hpp"
//#include <QTabWidget>
//#include <QDialogButtonBox>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSlider;
class QHBoxLayout;
class QVBoxLayout;

class Colorimetry : public QDialog
{
    Q_OBJECT

    private:
        //QTabWidget *tabWidget;
        //QDialogButtonBox *buttonBox;

        QHBoxLayout * horizontalLayoutForSliders;
        QVBoxLayout * verticalLayout;

        int width = 3;
        int height = 3;
        QSlider *** slidersTab;

        QPushButton * buttonDefaultValues;

        void geometry();
        void control();
        void appearance();

    public:
        Colorimetry(QWidget *parent = 0);

        cv::Mat getKernel();

    signals:
        void sigSlidersValueChanged();

    public slots:
        void sloSetDefaultValues();
        void sloSetRedFilter();
        void sloSetGreenFilter();
        void sloSetBlueFilter();
        void sloSetSepiaFilter();
        void sloSetBlackAndWhiteFilter();
};
