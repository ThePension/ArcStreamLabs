#include "animation.h"

#include "../../arcstreamlab.h"

#include <QPushButton>

Animation::Animation(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Animation");
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

void Animation::sloButtonMustacheAnimation()
{
    AnimationActions * mustacheAnimation = new MustacheAnimation();
    emit sigSetMustacheAnimation(mustacheAnimation);
}


void Animation::geometry()
{
    this->buttonMustacheAnimation = new QPushButton(this);
    this->buttonMustacheAnimation->setText(tr("Mustache animation"));

    this->verticalBox = new QVBoxLayout();
    this->verticalBox->addWidget(this->buttonMustacheAnimation);

    setLayout(this->verticalBox);
}

void Animation::control()
{
    connect(this->buttonMustacheAnimation, &QPushButton::clicked, this, &Animation::sloButtonMustacheAnimation);
}

void Animation::appearance()
{
    this->setStyleSheet("background : url(:/img/back6.png)");
}
