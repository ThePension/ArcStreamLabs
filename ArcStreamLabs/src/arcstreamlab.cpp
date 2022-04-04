#include "arcstreamlab.h"

ArcStreamLab::ArcStreamLab(QWidget *parent) : QWidget(parent)
{
    createUIGeometry();
    createUIAppearance();
    createUIControl();
}

void ArcStreamLab::createUIGeometry()
{
    // Horizontal Layout
    this->buttonsHLayout = new QHBoxLayout();
    this->displayHLayout = new QHBoxLayout();
    this->settingsHLayout = new QHBoxLayout();

    // Vertical Layout
    this->colorimetryVLayout = new QVBoxLayout();
    this->filterVLayout = new QVBoxLayout();
    this->specialEffectVLayout = new QVBoxLayout();
    this->animationVLayout = new QVBoxLayout();

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

    // Label
    this->lblVSeparator = new QLabel();
    this->lblHSeparator1 = new QLabel();
    this->lblHSeparator2 = new QLabel();
    this->lblHSeparator3 = new QLabel();

    this->lblColorimetry = new QLabel("Colorimetry");
    this->lblFilter = new QLabel("Filter");
    this->lblSpecialEffect = new QLabel("Special Effect");
    this->lblAnimation = new QLabel("Animation");

    // Composition Settings (Colorimetry, Filter, etc)
    this->colorimetryVLayout->addWidget(this->lblColorimetry);
    this->colorimetryVLayout->addSpacing(60);
    this->colorimetryVLayout->addWidget(this->btnColor);

    this->filterVLayout->addWidget(this->lblFilter);
    this->filterVLayout->addSpacing(60);
    this->filterVLayout->addWidget(this->btnFilter);

    this->specialEffectVLayout->addWidget(this->lblSpecialEffect);
    this->specialEffectVLayout->addSpacing(60);
    this->specialEffectVLayout->addWidget(this->btnSpecialEffect);

    this->animationVLayout->addWidget(this->lblAnimation);
    this->animationVLayout->addSpacing(60);
    this->animationVLayout->addWidget(this->btnAnimation);

    // Composition (other)
    this->buttonsHLayout->addWidget(this->btnPlay);
    this->buttonsHLayout->addWidget(this->btnPause);
    this->buttonsHLayout->addWidget(this->btnStop);

    this->videoInputVLayout->addWidget(this->graphicViewInput);
    this->videoInputVLayout->addLayout(this->buttonsHLayout);
    this->videoInputVLayout->addWidget(this->btnSnapshot);

    this->displayHLayout->addLayout(this->videoInputVLayout);
    this->displayHLayout->addWidget(this->graphicViewProcess);

    this->settingsHLayout->addLayout(this->colorimetryVLayout);
    this->settingsHLayout->addWidget(this->lblHSeparator1);
    this->settingsHLayout->addLayout(this->filterVLayout);
    this->settingsHLayout->addWidget(this->lblHSeparator2);
    this->settingsHLayout->addLayout(this->specialEffectVLayout);
    this->settingsHLayout->addWidget(this->lblHSeparator3);
    this->settingsHLayout->addLayout(this->animationVLayout);

    this->mainVLayout->addLayout(this->displayHLayout);
    this->mainVLayout->addSpacing(10);
    this->mainVLayout->addWidget(this->lblVSeparator);
    this->mainVLayout->addLayout(this->settingsHLayout);

    // Display
    setLayout(this->mainVLayout);
}

void ArcStreamLab::createUIAppearance()
{
    // Font
    QFont font;
    font.setPixelSize(35);
    font.setWeight(QFont::Normal);

    // Vertical layout
    this->colorimetryVLayout->setAlignment(Qt::AlignTop);
    this->filterVLayout->setAlignment(Qt::AlignTop);
    this->specialEffectVLayout->setAlignment(Qt::AlignTop);
    this->animationVLayout->setAlignment(Qt::AlignTop);

    // Graphics view
    this->graphicViewInput->setMaximumSize(20*this->formatWidth, 20*this->formatHeight);
    this->graphicViewProcess->setMaximumSize(55*this->formatWidth, 55*this->formatHeight);

    // Label
    this->lblColorimetry->setFont(font);
    this->lblColorimetry->setAlignment(Qt::AlignCenter);
    this->lblFilter->setFont(font);
    this->lblFilter->setAlignment(Qt::AlignCenter);
    this->lblSpecialEffect->setFont(font);
    this->lblSpecialEffect->setAlignment(Qt::AlignCenter);
    this->lblAnimation->setFont(font);
    this->lblAnimation->setAlignment(Qt::AlignCenter);

    this->lblVSeparator->setStyleSheet("border-top: 1px solid black;");
    this->lblVSeparator->setMaximumHeight(20);

    this->lblHSeparator1->setStyleSheet("border: 1px solid black;");
    this->lblHSeparator1->setMaximumWidth(1);

    this->lblHSeparator2->setStyleSheet("border: 1px solid black;");
    this->lblHSeparator2->setMaximumWidth(1);

    this->lblHSeparator3->setStyleSheet("border: 1px solid black;");
    this->lblHSeparator3->setMaximumWidth(1);

    // Button
    imageButtons();
    font.setPixelSize(20);

    this->btnColor->setFont(font);
    this->btnFilter->setFont(font);
    this->btnSpecialEffect->setFont(font);
    this->btnAnimation->setFont(font);

    this->btnAnimation->setMinimumHeight(50);
    this->btnFilter->setMinimumHeight(50);
    this->btnColor->setMinimumHeight(50);
    this->btnSpecialEffect->setMinimumHeight(50);
}

void ArcStreamLab::createUIControl()
{
    Colorimetry *colorDialog = new Colorimetry(this);
    connect(this->btnColor, &QPushButton::clicked, colorDialog, &QDialog::show);

    Filter *filterDialog =  new Filter(this);
    connect(this->btnFilter, &QPushButton::clicked, filterDialog, &QDialog::show);

    SpecialEffect *specialEffectDialog =  new SpecialEffect(this);
    connect(this->btnSpecialEffect, &QPushButton::clicked, specialEffectDialog, &QDialog::show);

    Animation *animationDialog =  new Animation(this);
    connect(this->btnAnimation, &QPushButton::clicked, animationDialog, &QDialog::show);
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

void ArcStreamLab::responsiveResize(float width)
{
    float w = width - 60.0;
    float units = w / this->formatWidth;
    float unitForLittleGV = (1.0/5.0) * units;
    float unitsForBigGV = units - unitForLittleGV;

    this->graphicViewInput->setMaximumSize(unitForLittleGV*this->formatWidth, unitForLittleGV*this->formatHeight);
    this->graphicViewInput->setMinimumSize(unitForLittleGV*this->formatWidth, unitForLittleGV*this->formatHeight);

    this->graphicViewProcess->setMaximumSize(unitsForBigGV*this->formatWidth, unitsForBigGV*this->formatHeight);
    this->graphicViewProcess->setMinimumSize(unitsForBigGV*this->formatWidth, unitsForBigGV*this->formatHeight);
}
