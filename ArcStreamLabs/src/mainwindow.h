#pragma once

#include <QMainWindow>
#include <opencv2/opencv.hpp>

#include "arcstreamlab.h"
#include "settings.h"
#include "aboutdialog.h"

QT_BEGIN_NAMESPACE
    namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        QAction *actImportSettings, *actExportSettings, *actExportSettingsAs, *actQuit, *actCancel;
        QAction *actAbout;
        QAction *actUndo, *actRedo;

        ArcStreamLab *arcStreamLab;

    public:
        MainWindow(QWidget *parent = nullptr);

    public slots:
        void displayAbout();

    private:
        void createMenusActions();
        void resizeEvent(QResizeEvent *event);
};
