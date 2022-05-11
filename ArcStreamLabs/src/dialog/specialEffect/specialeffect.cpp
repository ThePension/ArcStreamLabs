#include "specialeffect.h"
#include <QPushButton>
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
    //SpecialEffect * sobelFilter = new SobelFilter();
    //emit sigSetNoFilter(sobelFilter);
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

void SpecialEffect::geometry()
{
    this->buttonNoFilter = new QPushButton(this);
    this->buttonNoFilter->setText(tr("No filter"));

    this->buttonMirror = new QPushButton(this);
    this->buttonMirror->setText(tr("mirror"));

    this->buttonMosaicBlur = new QPushButton(this);
    this->buttonMosaicBlur->setText(tr("Mosaic blur"));

    this->verticalBox = new QVBoxLayout();
    this->verticalBox->addWidget(this->buttonNoFilter);
    this->verticalBox->addWidget(this->buttonMirror);
    this->verticalBox->addWidget(this->buttonMosaicBlur);
    setLayout(this->verticalBox);
}

void SpecialEffect::control()
{
    connect(this->buttonNoFilter, &QPushButton::clicked, this, &SpecialEffect::sloButtonNoFilter);
    connect(this->buttonMirror, &QPushButton::clicked, this, &SpecialEffect::sloMirrorEffect);
    connect(this->buttonMosaicBlur, &QPushButton::clicked, this, &SpecialEffect::sloMosaicBlurEffect);
}

void SpecialEffect::appearance()
{
    this->setStyleSheet("background : url(:/img/back6.png)");
}
