#include "arcstreamlab.h"

ArcStreamLab::ArcStreamLab(QWidget *parent) : QWidget(parent)
{
    actionManager = new ActionManager();
    rawStream = new VideoStream();
    circularBuffer = new CircularBuffer(100);
    processedStream = new ImageProcessing(circularBuffer, this->actionManager);
    createUIGeometry();
    createUIAppearance();
    createUIControl();

    graphicViewInput->setScene(new QGraphicsScene(this));
    graphicViewInput->setBackgroundBrush(QColor( "black"));
    graphicViewInput->scene()->addItem(&inputPixmap);
    graphicViewProcess->setScene(new QGraphicsScene(this));
    graphicViewProcess->setBackgroundBrush(QColor( "black"));
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

    this->btnColor = new QPushButton("Colorimetry");
    this->btnFilter = new QPushButton("Filters");
    this->btnSpecialEffect = new QPushButton("Special effect");
    this->btnAnimation = new QPushButton("Animation");

    // Graphics View
    this->graphicViewInput = new QGraphicsView();
    this->graphicViewProcess = new QGraphicsView();

    // Composition Settings (Colorimetry, Filter, etc)
    this->colorimetryVLayout->addWidget(this->btnColor);
    this->colorimetryVLayout->addSpacing(15);

    this->filterVLayout->addWidget(this->btnFilter);
    this->filterVLayout->addSpacing(15);

    this->specialEffectVLayout->addWidget(this->btnSpecialEffect);
    this->specialEffectVLayout->addSpacing(15);

    this->animationVLayout->addWidget(this->btnAnimation);
    this->animationVLayout->addSpacing(15);

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
    this->settingsHLayout->addLayout(this->filterVLayout);
    this->settingsHLayout->addLayout(this->specialEffectVLayout);
    this->settingsHLayout->addLayout(this->animationVLayout);

    this->mainVLayout->addLayout(this->displayGridLayout);
    this->mainVLayout->addSpacing(10);
    this->mainVLayout->addLayout(this->settingsHLayout);

    // Dialog
    colorDialog = new Colorimetry(this->actionManager, this);
    colorimetryFilter = new ColorimetryFilter(this);
    colorimetryTabs = new ColorimetryTabs(colorDialog, colorimetryFilter, this);
    filterDialog =  new Filter(this);
    specialEffectDialog =  new SpecialEffect(this);
    animationDialog =  new Animation(this);

    // Settings
    this->settings = new Settings(colorDialog, filterDialog, specialEffectDialog, animationDialog, this);

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

    // Button
    imageButtons();
    font.setPixelSize(38);


    this->btnColor->setFont(font);
    this->btnFilter->setFont(font);
    this->btnSpecialEffect->setFont(font);
    this->btnAnimation->setFont(font);

    this->btnAnimation->setMinimumHeight(100);
    this->btnAnimation->setMaximumHeight(100);
    this->btnFilter->setMinimumHeight(100);
    this->btnFilter->setMaximumHeight(100);
    this->btnColor->setMinimumHeight(100);
    this->btnColor->setMaximumHeight(100);
    this->btnSpecialEffect->setMinimumHeight(100);
    this->btnSpecialEffect->setMaximumHeight(100);

    this->btnPause->setEnabled(false);
    this->btnStop->setEnabled(false);
    this->btnSnapshot->setEnabled(false);

    QString btnDrawStylesheet =
        "QPushButton:hover {"
            "background-color: gray;"
            "border: 1px black solid;"
        "}";

    this->btnPlay->setStyleSheet(btnDrawStylesheet);
    this->btnPause->setStyleSheet(btnDrawStylesheet);
    this->btnStop->setStyleSheet(btnDrawStylesheet);
    this->btnSnapshot->setStyleSheet(btnDrawStylesheet);

    //BackGround text button
    this->setStyleSheet("QPushButton {color: black; background-color: transparent}");
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
    connect(btnSnapshot, &QPushButton::clicked, this, &ArcStreamLab::sloSaveSnapshot);

    // connection with the dialog box
    connect(this->btnColor, &QPushButton::clicked, colorimetryTabs, &QDialog::show);
    connect(this->btnFilter, &QPushButton::clicked, filterDialog, &QDialog::show);
    connect(this->btnSpecialEffect, &QPushButton::clicked, specialEffectDialog, &QDialog::show);
    connect(this->btnAnimation, &QPushButton::clicked, animationDialog, &QDialog::show);

    connect(colorDialog, &Colorimetry::sigSlidersValueChanged, this, &ArcStreamLab::sloUpdateColorimetryValues);

    connect(colorimetryFilter, &ColorimetryFilter::sigSetDefaultFilter, colorDialog, &Colorimetry::sloSetDefaultValues);
    connect(colorimetryFilter, &ColorimetryFilter::sigSetRedFilter, colorDialog, &Colorimetry::sloSetRedFilter);
    connect(colorimetryFilter, &ColorimetryFilter::sigSetGreenFilter, colorDialog, &Colorimetry::sloSetGreenFilter);
    connect(colorimetryFilter, &ColorimetryFilter::sigSetBlueFilter, colorDialog, &Colorimetry::sloSetBlueFilter);
    connect(colorimetryFilter, &ColorimetryFilter::sigSetSepiaFilter, colorDialog, &Colorimetry::sloSetSepiaFilter);
    connect(colorimetryFilter, &ColorimetryFilter::sigSetBlackAndWhiteFilter, colorDialog, &Colorimetry::sloSetBlackAndWhiteFilter);
    connect(colorimetryFilter, &ColorimetryFilter::sigSetAlienFilter, colorDialog, &Colorimetry::sloSetAlienFilter);

    sloUpdateColorimetryValues();

    connect(filterDialog, &Filter::sigSetLongExposureFilter, this, &ArcStreamLab::sloCreateFilterAction);
    connect(filterDialog, &Filter::sigSetSobelFilter, this, &ArcStreamLab::sloCreateFilterAction);
    connect(filterDialog, &Filter::sigSetStylizationFilter, this, &ArcStreamLab::sloCreateFilterAction);
    connect(filterDialog, &Filter::sigSetNoFilter, this, &ArcStreamLab::sloNoFilter);

    connect(specialEffectDialog, &SpecialEffect::sigSetMirrorEffect, this, &ArcStreamLab::sloCreateEffectAction);
    connect(specialEffectDialog, &SpecialEffect::sigSetMosaicBlurEffect, this, &ArcStreamLab::sloCreateEffectAction);
    connect(specialEffectDialog, &SpecialEffect::sigSetNoSpecialEffects, this, &ArcStreamLab::sloNoSpecialEffects);
    connect(specialEffectDialog, &SpecialEffect::sigMosaicTileSizeChanged, this, &ArcStreamLab::sloUpdateMosaicTileSize);
    connect(specialEffectDialog, &SpecialEffect::sigSetFacialBlurEffect, this, &ArcStreamLab::sloCreateEffectAction);

    connect(animationDialog, &Animation::sigSetMustacheAnimation, this, &ArcStreamLab::sloCreateAnimationAction);
    connect(animationDialog, &Animation::sigSetTextAnimation, this, &ArcStreamLab::sloCreateAnimationAction);

    this->settings = new Settings(colorDialog, filterDialog, specialEffectDialog, animationDialog, this);
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
    this->btnPause->setEnabled(true);
    this->btnStop->setEnabled(true);
    this->btnSnapshot->setEnabled(true);
    this->btnPlay->setEnabled(false);

    rawStream->start(QThread::HighPriority);
    processedStream->start(QThread::LowPriority);
}

void ArcStreamLab::sloPauseButtonClicked()
{
    this->rawStream->terminate();
    this->processedStream->terminate();
    this->circularBuffer->reset();

    this->btnPause->setEnabled(false);
    this->btnStop->setEnabled(false);
    this->btnSnapshot->setEnabled(false);
    this->btnPlay->setEnabled(true);
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

Settings *ArcStreamLab::getSettings()
{
    return this->settings;
}

void ArcStreamLab::undo()
{
    this->actionManager->undo();
}

void ArcStreamLab::redo()
{
    this->actionManager->redo();
}

void ArcStreamLab::sloSaveSnapshot()
{
    // Get the current displayed image
    QPixmap snapshot = graphicViewProcess->grab();

    // Get the file name
    QString fileName = QFileDialog::getSaveFileName(this, tr("Sauver"), "./", tr("Dessins (*.PNG)"));

    if (!fileName.isEmpty())
    {
        // Create the file
        QFile file(fileName);

        // Open the file
        if (!file.open(QFile::WriteOnly))
        {
            QMessageBox::critical(this, tr("Erreur"), tr("Erreur lors de la sauvegarde de l'instantanée"));
            return;
        }

        // Save the QPixmap into the file
        snapshot.save(&file, "PNG");
    }
}

void ArcStreamLab::sloCreateFilterAction(FilterActions * filterAction)
{
    this->actionManager->addAction(filterAction);
}

void ArcStreamLab::sloCreateEffectAction(SpecialEffectActions * specialEffectAction)
{
    MosaicBlurEffect * mbe = dynamic_cast<MosaicBlurEffect *>(specialEffectAction);

    if(mbe != nullptr)
    {
        if(this->mosaicEffect == nullptr)
        {
            this->mosaicEffect = mbe;
            this->actionManager->addAction(specialEffectAction);
        }
    }
    else
    {
        this->actionManager->addAction(specialEffectAction);
    }
}

void ArcStreamLab::sloNoFilter()
{
    this->actionManager->removeFilters();
}

void ArcStreamLab::sloNoSpecialEffects()
{
    this->actionManager->removeSpecialEffects();
    this->mosaicEffect = nullptr;
}

void ArcStreamLab::sloUpdateMosaicTileSize(int tileSize)
{
    if(this->mosaicEffect != nullptr)
    {
        this->mosaicEffect->setTileSize(tileSize);
    }
}

void ArcStreamLab::sloCreateAnimationAction(AnimationActions * animationAction)
{
    this->actionManager->addAction(animationAction);
}

