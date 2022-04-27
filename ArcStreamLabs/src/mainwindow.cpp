#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->arcStreamLab = new ArcStreamLab();
    setCentralWidget(this->arcStreamLab);

    setWindowTitle("Arc Stream Labs");
    resize(1200,800);

    this->arcStreamLab->responsiveResize();

    createMenusActions();
}

void MainWindow::createMenusActions()
{
    actImportSettings = new QAction(tr("&Ouvrir"), this);
    actExportSettings = new QAction(tr("&Enregistrer"), this);
    actExportSettingsAs = new QAction(tr("Enregistrer &Sous"), this);
    actQuit = new QAction(tr("&Quitter"), this);
    actChangeThick = new QAction(tr("&Epaisseur"), this);
    actChangePen = new QAction(tr("Couleur &tracé"), this);
    actChangeBrush = new QAction(tr("Couleur &remplissage"), this);

    actZoomIn = new QAction(tr("Zoom &In"), this);
    actZoomOut = new QAction(tr("Zoom &Out"), this);
    actZoomReset = new QAction(tr("&Echelle 1:1"), this);

    actAbout = new QAction(tr("A &Propos"), this);

    actExportSettings->setShortcut(tr("Ctrl+S"));

    QMenu* menuFichier = menuBar()->addMenu(tr("&Fichier"));
    menuFichier->addAction(actImportSettings);
    menuFichier->addAction(actExportSettings);
    menuFichier->addAction(actExportSettingsAs);
    menuFichier->addAction(actQuit);

    connect(actExportSettings, &QAction::triggered, this->arcStreamLab->getSettings(), &Settings::exportSettings);
    connect(actExportSettingsAs, &QAction::triggered, this->arcStreamLab->getSettings(), &Settings::exportSettingsAs);

    QMenu* menuDraw = menuBar()->addMenu(tr("&Dessin"));
    menuDraw->addAction(actChangeThick);
    menuDraw->addAction(actChangePen);
    menuDraw->addAction(actChangeBrush);

    QMenu* menuZoom = menuBar()->addMenu(tr("&Zoom"));
    menuZoom->addAction(actZoomIn);
    menuZoom->addAction(actZoomOut);
    menuZoom->addAction(actZoomReset);

    QMenu* menuHelp = menuBar()->addMenu(tr("&?"));
    menuHelp->addAction(actAbout);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    this->arcStreamLab->responsiveResize();
}
