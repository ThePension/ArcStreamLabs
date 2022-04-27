#pragma once

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QMutex>

#include "arcstreamlab.h"
#include "settings.h"

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        QAction *actNew, *actOpen, *actSave, *actQuit, *actCancel;
        QAction *actChangeThick, *actChangePen, *actChangeBrush;
        QAction *actZoomIn, *actZoomOut, *actZoomReset, *actHelp, *actAbout;

        ArcStreamLab *arcStreamLab;

        QMutex mutex;
        cv::Mat mat;

    public:
        MainWindow(QWidget *parent = nullptr);

    private:
        void createMenusActions();

        void resizeEvent(QResizeEvent *event);
};
