#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    configureUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::configureUI()
{
    QPixmap play = QPixmap(":/Images/Play.png");
    play = play.scaled(50, 50, Qt::KeepAspectRatio);
    ui->btnPlay->setIcon(play);
    ui->btnPlay->setFlat(true);
    ui->btnPlay->setFocusPolicy(Qt::NoFocus);
    ui->btnPlay->setIconSize(play.size());
    ui->btnPlay->setStyleSheet("QPushButton:flat:pressed { border: none; };");

    QPixmap pause = QPixmap(":/Images/Pause.png");
    pause = pause.scaled(50, 50, Qt::KeepAspectRatio);
    ui->btnPause->setIcon(pause);
    ui->btnPause->setFlat(true);
    ui->btnPause->setFocusPolicy(Qt::NoFocus);
    ui->btnPause->setIconSize(pause.size());
    ui->btnPause->setStyleSheet("QPushButton:flat:pressed { border: none; };");

    QPixmap stop = QPixmap(":/Images/Stop.png");
    stop = stop.scaled(50, 50, Qt::KeepAspectRatio);
    ui->btnStop->setIcon(stop);
    ui->btnStop->setFlat(true);
    ui->btnStop->setFocusPolicy(Qt::NoFocus);
    ui->btnStop->setIconSize(stop.size());
    ui->btnStop->setStyleSheet("QPushButton:flat:pressed { border: none; };");

    QPixmap snapshot = QPixmap(":/Images/Snapshot.png");
    snapshot = snapshot.scaled(80, 80, Qt::KeepAspectRatio);
    ui->btnInstantane->setIcon(snapshot);
    ui->btnInstantane->setFlat(true);
    ui->btnInstantane->setFocusPolicy(Qt::NoFocus);
    ui->btnInstantane->setIconSize(snapshot.size());
    ui->btnInstantane->setStyleSheet("QPushButton:flat:pressed { border: none; };");
}

