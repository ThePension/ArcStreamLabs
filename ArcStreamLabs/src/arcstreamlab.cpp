#include "arcstreamlab.h"

ArcStreamLab::ArcStreamLab(QWidget *parent) : QWidget(parent)
{
    rawStream = new VideoStream();
    circularBuffer = new ArcStreamLabs::LibCircularBuffer::CircularBuffer(1000);
    processedStream = new ImageProcessing(circularBuffer);
    createUIGeometry();
    createUIAppearance();
    createUIControl();
    graphicViewInput->setScene(new QGraphicsScene(this));
    graphicViewInput->scene()->addItem(&inputPixmap);
    graphicViewProcess->setScene(new QGraphicsScene(this));
    graphicViewProcess->scene()->addItem(&outputPixmap);
}

void ArcStreamLab::createUIGeometry()
{
    // Horizontal Layout
    this->buttonsHLayout = new QHBoxLayout();
    this->settingsHLayout = new QHBoxLayout();

    // Vertical Layout
    this->colorimetryVLayout = new QVBoxLayout();
    this->filterVLayout = new QVBoxLayout();
    this->specialEffectVLayout = new QVBoxLayout();
    this->animationVLayout = new QVBoxLayout();

    this->videoInputVLayout = new QVBoxLayout();
    this->mainVLayout = new QVBoxLayout();

    // Grid Layout
    this->displayGridLayout = new QGridLayout();

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
    this->colorimetryVLayout->addSpacing(40);
    this->colorimetryVLayout->addWidget(this->btnColor);
    this->colorimetryVLayout->addSpacing(20);

    this->filterVLayout->addWidget(this->lblFilter);
    this->filterVLayout->addSpacing(40);
    this->filterVLayout->addWidget(this->btnFilter);
    this->filterVLayout->addSpacing(20);

    this->specialEffectVLayout->addWidget(this->lblSpecialEffect);
    this->specialEffectVLayout->addSpacing(40);
    this->specialEffectVLayout->addWidget(this->btnSpecialEffect);
    this->specialEffectVLayout->addSpacing(20);

    this->animationVLayout->addWidget(this->lblAnimation);
    this->animationVLayout->addSpacing(40);
    this->animationVLayout->addWidget(this->btnAnimation);
    this->animationVLayout->addSpacing(20);

    // Composition (other)
    this->buttonsHLayout->addWidget(this->btnPlay);
    this->buttonsHLayout->addWidget(this->btnPause);
    this->buttonsHLayout->addWidget(this->btnStop);

    this->videoInputVLayout->addWidget(this->graphicViewInput);
    this->videoInputVLayout->addLayout(this->buttonsHLayout);
    this->videoInputVLayout->addWidget(this->btnSnapshot);

    this->displayGridLayout->addLayout(this->videoInputVLayout, 0, 0);
    this->displayGridLayout->addWidget(this->graphicViewProcess, 0, 1);

    this->settingsHLayout->addLayout(this->colorimetryVLayout);
    this->settingsHLayout->addWidget(this->lblHSeparator1);
    this->settingsHLayout->addLayout(this->filterVLayout);
    this->settingsHLayout->addWidget(this->lblHSeparator2);
    this->settingsHLayout->addLayout(this->specialEffectVLayout);
    this->settingsHLayout->addWidget(this->lblHSeparator3);
    this->settingsHLayout->addLayout(this->animationVLayout);

    this->mainVLayout->addLayout(this->displayGridLayout);
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

    this->displayGridLayout->setColumnStretch(0, 1);
    this->displayGridLayout->setColumnStretch(1, 3);

    // Label
    this->lblColorimetry->setFont(font);
    this->lblColorimetry->setAlignment(Qt::AlignCenter);
    this->lblColorimetry->setMaximumHeight(this->lblColorimetry->height());
    this->lblFilter->setFont(font);
    this->lblFilter->setAlignment(Qt::AlignCenter);
    this->lblFilter->setMaximumHeight(this->lblFilter->height());
    this->lblSpecialEffect->setFont(font);
    this->lblSpecialEffect->setAlignment(Qt::AlignCenter);
    this->lblSpecialEffect->setMaximumHeight(this->lblSpecialEffect->height());
    this->lblAnimation->setFont(font);
    this->lblAnimation->setAlignment(Qt::AlignCenter);
    this->lblAnimation->setMaximumHeight(this->lblAnimation->height());

    this->lblVSeparator->setStyleSheet("QLabel { border-top: 1px solid black; }");
    this->lblVSeparator->setMaximumHeight(20);
    this->lblVSeparator->setMinimumHeight(20);

    this->lblHSeparator1->setStyleSheet("QLabel { border: 1px solid black; }");
    this->lblHSeparator1->setMaximumWidth(1);

    this->lblHSeparator2->setStyleSheet("QLabel { border: 1px solid black; }");
    this->lblHSeparator2->setMaximumWidth(1);

    this->lblHSeparator3->setStyleSheet("QLabel { border: 1px solid black; }");
    this->lblHSeparator3->setMaximumWidth(1);

    // Button
    imageButtons();
    font.setPixelSize(20);

    this->btnColor->setFont(font);
    this->btnFilter->setFont(font);
    this->btnSpecialEffect->setFont(font);
    this->btnAnimation->setFont(font);

    this->btnAnimation->setMinimumHeight(50);
    this->btnAnimation->setMaximumHeight(50);
    this->btnFilter->setMinimumHeight(50);
    this->btnFilter->setMaximumHeight(50);
    this->btnColor->setMinimumHeight(50);
    this->btnColor->setMaximumHeight(50);
    this->btnSpecialEffect->setMinimumHeight(50);
    this->btnSpecialEffect->setMaximumHeight(50);

    // Graphics view
    //this->graphicViewInput->setMaximumHeight(5*this->formatHeight);
}

void ArcStreamLab::createUIControl()
{
    //connect the stream video
    connect(rawStream, &VideoStream::newPixmapCaptured, this, &ArcStreamLab::sloUpdateRawStreamValue);
    connect(processedStream, &ImageProcessing::imagedProcessed, this, &ArcStreamLab::sloUpdateProcessedStreamValue);

    // Stream buttons
    connect(btnPlay, &QPushButton::clicked, this, &ArcStreamLab::sloPlayButtonClicked);
    connect(btnStop, &QPushButton::clicked, this, &ArcStreamLab::sloStopButtonClicked);
    connect(btnPause, &QPushButton::clicked, this, &ArcStreamLab::sloPauseButtonClicked);

    // connection with the dialog box
    colorDialog = new Colorimetry(this);
    connect(this->btnColor, &QPushButton::clicked, colorDialog, &QDialog::show);
    connect(colorDialog, &Colorimetry::sigSlidersValueChanged, this, &ArcStreamLab::sloUpdateColorimetryValues);

    sloUpdateColorimetryValues();

    filterDialog =  new Filter(this);
    connect(this->btnFilter, &QPushButton::clicked, filterDialog, &QDialog::show);
    connect(filterDialog, &Filter::sigSetSepiaFilter, colorDialog, &Colorimetry::sloSetSepiaFilter);

    specialEffectDialog =  new SpecialEffect(this);
    connect(this->btnSpecialEffect, &QPushButton::clicked, specialEffectDialog, &QDialog::show);

    animationDialog =  new Animation(this);
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

    QPixmap pause = QPixmap(":/img/Pause.png");
    pause = pause.scaled(50, 50, Qt::KeepAspectRatio);
    this->btnPause->setIcon(pause);
    this->btnPause->setFlat(true);
    this->btnPause->setFocusPolicy(Qt::NoFocus);
    this->btnPause->setIconSize(pause.size());

    QPixmap stop = QPixmap(":/img/Stop.png");
    stop = stop.scaled(50, 50, Qt::KeepAspectRatio);
    this->btnStop->setIcon(stop);
    this->btnStop->setFlat(true);
    this->btnStop->setFocusPolicy(Qt::NoFocus);
    this->btnStop->setIconSize(stop.size());

    QPixmap snapshot = QPixmap(":/img/Snapshot.png");
    snapshot = snapshot.scaled(80, 80, Qt::KeepAspectRatio);
    this->btnSnapshot->setIcon(snapshot);
    this->btnSnapshot->setFlat(true);
    this->btnSnapshot->setFocusPolicy(Qt::NoFocus);
    this->btnSnapshot->setIconSize(snapshot.size());
}

void ArcStreamLab::sloUpdateRawStreamValue()
{
    inputPixmap.setPixmap(rawStream->pixmap());
    graphicViewInput->fitInView(&inputPixmap, Qt::KeepAspectRatio);
    circularBuffer->put(rawStream->frame());
}

void ArcStreamLab::sloUpdateProcessedStreamValue()
{
    outputPixmap.setPixmap(processedStream->pixmap());
    graphicViewProcess->fitInView(&outputPixmap, Qt::KeepAspectRatio);
}

void ArcStreamLab::sloPlayButtonClicked()
{
    rawStream->start(QThread::HighPriority);
    processedStream->start(QThread::LowPriority);
}

void ArcStreamLab::sloPauseButtonClicked()
{
    this->rawStream->terminate();
    this->processedStream->terminate();
    this->circularBuffer->reset();
}

void ArcStreamLab::sloStopButtonClicked()
{
    this->rawStream->terminate();
    this->processedStream->terminate();
    this->circularBuffer->reset();
    QApplication::quit();
}

void ArcStreamLab::sloUpdateColorimetryValues()
{
    this->processedStream->setKernel(this->colorDialog->getKernel());
}

void ArcStreamLab::responsiveResize()
{
    float w = this->graphicViewInput->width();
    float units = w / this->formatWidth;

    this->graphicViewInput->setMaximumHeight(units*this->formatHeight);
}
