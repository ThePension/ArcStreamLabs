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

using namespace cv;

class Colorimetry : public QDialog
{
    Q_OBJECT

    private:
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

        Mat getKernel();
        QSlider *** getSlidersTab();
        int getWidth();
        int getHeight();
        void setKernel(Mat);

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
