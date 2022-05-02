#pragma once

#include <QDialog>
#include "opencv2/opencv.hpp"
//#include <QTabWidget>
//#include <QDialogButtonBox>

#include "colorimetryactions.h"
#include "LibUndoRedo/actionmanager.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QSlider;
class QHBoxLayout;
class QVBoxLayout;
class QAction;
class ArcStreamLab;

class Colorimetry : public QDialog
{
    Q_OBJECT

    private:
        //QTabWidget *tabWidget;
        //QDialogButtonBox *buttonBox;

        ActionManager *actionManager;
        ArcStreamLab *parent;
        QAction *actUndo, *actRedo;

        QHBoxLayout * horizontalLayoutForSliders;
        QVBoxLayout * verticalLayout;

        int width = 3;
        int height = 3;
        QSlider *** slidersTab;
        int **tempBackupValues;

        QPushButton * buttonDefaultValues;

        void geometry();
        void control();
        void appearance();
        ColorimetryActions* createColorimetryAction(int **colorValues);
        void defaultValues();
        void redirectAction();

    public:
        Colorimetry(ActionManager *actionManager, QWidget *parent = 0);
        ~Colorimetry();

        cv::Mat getKernel();
        QSlider *** getSlidersTab();
        int getWidth();
        int getHeight();
        void setKernel(cv::Mat);

    signals:
        void sigSlidersValueChanged();

    public slots:
        void createReleaseAction();
        void backupSliderValues();
        void sloSetDefaultValues();
        void sloSetRedFilter();
        void sloSetGreenFilter();
        void sloSetBlueFilter();
        void sloSetSepiaFilter();
        void sloSetBlackAndWhiteFilter();
};
