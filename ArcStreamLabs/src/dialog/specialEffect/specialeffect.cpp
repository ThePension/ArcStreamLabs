#include "specialeffect.h"
#include <QPushButton>
#include <QSlider>
#include "../../arcstreamlab.h"

SpecialEffect::SpecialEffect(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Special Effect");
    resize(200, 100);

    geometry();
    control();
    appearance();

    this->parent = static_cast<ArcStreamLab*>(parent);

    actUndo = new QAction("undo", this);
    actUndo->setShortcut(QKeySequence("Ctrl+Z"));
    connect(actUndo, &QAction::triggered, this->parent, &ArcStreamLab::undo);

    actRedo = new QAction("redo", this);
    actRedo->setShortcut(QKeySequence("Ctrl+Y"));
    connect(actRedo, &QAction::triggered, this->parent, &ArcStreamLab::redo);

    addAction(actUndo);
    addAction(actRedo);
}

void SpecialEffect::sloButtonNoFilter()
{
    emit sigSetNoSpecialEffects();
}

void SpecialEffect::sloMirrorEffect()
{
    SpecialEffectActions * mirror = new Mirror();
    emit sigSetMirrorEffect(mirror);
}

void SpecialEffect::sloMosaicBlurEffect()
{
    SpecialEffectActions * mosaicBlurEffect = new MosaicBlurEffect();
    emit sigSetMosaicBlurEffect(mosaicBlurEffect);
}

void SpecialEffect::sloMosaicSlider()
{
    //this->mosaicTileSize = this->mosaicSlider->value();
    emit sigMosaicTileSizeChanged(this->mosaicSlider->value());
}

void SpecialEffect::geometry()
{
    this->buttonNoFilter = new QPushButton(this);
    this->buttonNoFilter->setText(tr("No special effects"));

    this->buttonMirror = new QPushButton(this);
    this->buttonMirror->setText(tr("mirror"));

    this->buttonMosaicBlur = new QPushButton(this);
    this->buttonMosaicBlur->setText(tr("Mosaic blur"));

    this->mosaicSlider = new QSlider(Qt::Horizontal, this);
    this->mosaicSlider->setTickInterval(1);
    this->mosaicSlider->setRange(1, 50);
    this->mosaicSlider->setValue(16);

    QHBoxLayout *mosaicLayout = new QHBoxLayout();
    mosaicLayout->addWidget(this->buttonMosaicBlur);
    mosaicLayout->addWidget(this->mosaicSlider);

    this->verticalBox = new QVBoxLayout();
    this->verticalBox->addWidget(this->buttonNoFilter);
    this->verticalBox->addWidget(this->buttonMirror);
    this->verticalBox->addLayout(mosaicLayout);

    setLayout(this->verticalBox);
}

void SpecialEffect::control()
{
    connect(this->buttonNoFilter, &QPushButton::clicked, this, &SpecialEffect::sloButtonNoFilter);
    connect(this->buttonMirror, &QPushButton::clicked, this, &SpecialEffect::sloMirrorEffect);
    connect(this->buttonMosaicBlur, &QPushButton::clicked, this, &SpecialEffect::sloMosaicBlurEffect);
    connect(this->mosaicSlider, &QSlider::valueChanged, this, &SpecialEffect::sloMosaicSlider);
}

void SpecialEffect::appearance()
{
    this->setStyleSheet("background : url(:/img/back6.png)");
}
