#include "arcstreamlab.h"

ArcStreamLab::ArcStreamLab(QWidget *parent) : QWidget(parent)
{
    createUIGeometry();
    createUIAppearance();
}

void ArcStreamLab::createUIGeometry()
{
    // Layout
    this->buttonsHLayout = new QHBoxLayout();
    this->displayHLayout = new QHBoxLayout();
    this->settingsHLayout = new QHBoxLayout();

    this->videoInputVLayout = new QVBoxLayout();
    this->mainVLayout = new QVBoxLayout();

    // Buttons
    this->btnPlay = new QPushButton();
    this->btnPause = new QPushButton();
    this->btnStop = new QPushButton();
    this->btnSnapshot = new QPushButton();

    this->btnColor = new QPushButton("Paramètres");
    this->btnFilter = new QPushButton("Paramètres");
    this->btnSpecialEffect = new QPushButton("Paramètres");
    this->btnAnimation = new QPushButton("Paramètres");

    // Graphics View
    this->graphicViewInput = new QGraphicsView();
    this->graphicViewProcess = new QGraphicsView();

    // Composition
    this->buttonsHLayout->addWidget(this->btnPlay);
    this->buttonsHLayout->addWidget(this->btnPause);
    this->buttonsHLayout->addWidget(this->btnStop);

    this->videoInputVLayout->addWidget(this->graphicViewInput);
    this->videoInputVLayout->addLayout(this->buttonsHLayout);
    this->videoInputVLayout->addWidget(this->btnSnapshot);

    this->displayHLayout->addLayout(this->videoInputVLayout);
    this->displayHLayout->addWidget(this->graphicViewProcess);

    this->settingsHLayout->addWidget(this->btnColor);
    this->settingsHLayout->addWidget(this->btnFilter);
    this->settingsHLayout->addWidget(this->btnSpecialEffect);
    this->settingsHLayout->addWidget(this->btnAnimation);

    this->mainVLayout->addLayout(this->displayHLayout);
    this->mainVLayout->addSpacing(100);
    this->mainVLayout->addLayout(this->settingsHLayout);

    // Display
    setLayout(this->mainVLayout);
}

void ArcStreamLab::createUIAppearance()
{
    imageButtons();
    this->graphicViewInput->setMaximumSize(20*this->GV_WIDTH, 20*this->GV_HEIGHT);
    this->graphicViewProcess->setMaximumSize(55*this->GV_WIDTH, 55*this->GV_HEIGHT);
}

void ArcStreamLab::imageButtons()
{
    QPixmap play = QPixmap(":/img/Play.png");
    play = play.scaled(50, 50, Qt::KeepAspectRatio);
    this->btnPlay->setIcon(play);
    this->btnPlay->setFlat(true);
    this->btnPlay->setFocusPolicy(Qt::NoFocus);
    this->btnPlay->setIconSize(play.size());
    this->btnPlay->setStyleSheet("QPushButton:flat:pressed { border: none; };");

    QPixmap pause = QPixmap(":/img/Pause.png");
    pause = pause.scaled(50, 50, Qt::KeepAspectRatio);
    this->btnPause->setIcon(pause);
    this->btnPause->setFlat(true);
    this->btnPause->setFocusPolicy(Qt::NoFocus);
    this->btnPause->setIconSize(pause.size());
    this->btnPause->setStyleSheet("QPushButton:flat:pressed { border: none; };");

    QPixmap stop = QPixmap(":/img/Stop.png");
    stop = stop.scaled(50, 50, Qt::KeepAspectRatio);
    this->btnStop->setIcon(stop);
    this->btnStop->setFlat(true);
    this->btnStop->setFocusPolicy(Qt::NoFocus);
    this->btnStop->setIconSize(stop.size());
    this->btnStop->setStyleSheet("QPushButton:flat:pressed { border: none; };");

    QPixmap snapshot = QPixmap(":/img/Snapshot.png");
    snapshot = snapshot.scaled(80, 80, Qt::KeepAspectRatio);
    this->btnSnapshot->setIcon(snapshot);
    this->btnSnapshot->setFlat(true);
    this->btnSnapshot->setFocusPolicy(Qt::NoFocus);
    this->btnSnapshot->setIconSize(snapshot.size());
    this->btnSnapshot->setStyleSheet("QPushButton:flat:pressed { border: none; };");
}
