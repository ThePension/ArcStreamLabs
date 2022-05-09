#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->arcStreamLab = new ArcStreamLab();
    setCentralWidget(this->arcStreamLab);

    setWindowTitle("Arc Stream Labs");
    resize(1200,800);

    this->arcStreamLab->responsiveResize();

    //set mainwindow background
    this->setStyleSheet("MainWindow {background : url(:/img/back6.png)}");

    createMenusActions();
}

void MainWindow::displayAbout()
{
    AboutDialog aboutDialog;
    aboutDialog.exec();
}

void MainWindow::createMenusActions()
{
    actImportSettings = new QAction(tr("&Importer paramètres"), this);
    actExportSettings = new QAction(tr("&Exporter paramètres"), this);
    actExportSettingsAs = new QAction(tr("Exporter paramètres &Sous"), this);
    actQuit = new QAction(tr("&Quitter"), this);
    actAbout = new QAction(tr("A &Propos"), this);
    actUndo = new QAction("undo", this);
    actRedo = new QAction("redo", this);

    actExportSettings->setShortcut(tr("Ctrl+S"));
    actUndo->setShortcut(QKeySequence("Ctrl+Z"));
    actRedo->setShortcut(QKeySequence("Ctrl+Y"));

    QMenu* menuFichier = menuBar()->addMenu(tr("&Fichier"));
    menuFichier->addAction(actUndo);
    menuFichier->addAction(actRedo);
    menuFichier->addAction(actQuit);

    QMenu* menuSettings = menuBar()->addMenu(tr("&Paramètres"));
    menuSettings->addAction(actImportSettings);
    menuSettings->addAction(actExportSettings);
    menuSettings->addAction(actExportSettingsAs);

    QMenu* menuHelp = menuBar()->addMenu(tr("&?"));
    menuHelp->addAction(actAbout);

    connect(actImportSettings, &QAction::triggered, this->arcStreamLab->getSettings(), &Settings::importSettings);
    connect(actExportSettings, &QAction::triggered, this->arcStreamLab->getSettings(), &Settings::exportSettings);
    connect(actExportSettingsAs, &QAction::triggered, this->arcStreamLab->getSettings(), &Settings::exportSettingsAs);
    connect(actQuit, &QAction::triggered, this, &QApplication::quit);
    connect(actAbout, &QAction::triggered, this, &MainWindow::displayAbout);
    connect(actUndo, &QAction::triggered, this->arcStreamLab, &ArcStreamLab::undo);
    connect(actRedo, &QAction::triggered, this->arcStreamLab, &ArcStreamLab::redo);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    this->arcStreamLab->responsiveResize();
}
