#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    arcStreamLab = new ArcStreamLab();
    setCentralWidget(this->arcStreamLab);

    setWindowTitle("Arc Stream Labs");
    resize(1200,800);

    this->arcStreamLab->responsiveResize(width());

    createMenusActions();
}

void MainWindow::createMenusActions()
{
    actNew = new QAction(tr("&Nouveau"),this);
    actOpen = new QAction(tr("&Ouvrir"),this);
    actSave = new QAction(tr("&Enregistrer"),this);
    actQuit = new QAction(tr("&Quitter"),this);
    actChangeThick = new QAction(tr("&Epaisseur"),this);
    actChangePen = new QAction(tr("Couleur &tracé"),this);
    actChangeBrush = new QAction(tr("Couleur &remplissage"),this);

    actZoomIn = new QAction(tr("Zoom &In"),this);
    actZoomOut = new QAction(tr("Zoom &Out"),this);
    actZoomReset = new QAction(tr("&Echelle 1:1"),this);

    actAbout = new QAction(tr("A &Propos"),this);

    QMenu* menuFichier = menuBar()->addMenu(tr("&Fichier"));
    menuFichier->addAction(actNew);
    menuFichier->addAction(actOpen);
    menuFichier->addAction(actSave);
    menuFichier->addAction(actQuit);

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
    this->arcStreamLab->responsiveResize(width());
}
