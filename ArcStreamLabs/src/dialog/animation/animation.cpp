#include "animation.h"

#include "../../arcstreamlab.h"

#include <QPushButton>
#include <QTextEdit>

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

void Animation::sloButtonTextAnimation()
{
    AnimationActions * textAnimation = new TextAnimation(this->lineEditText->text());
    emit sigSetTextAnimation(textAnimation);
}


void Animation::geometry()
{
    this->buttonMustacheAnimation = new QPushButton(this);
    this->buttonMustacheAnimation->setText(tr("Mustache animation"));

    this->buttonText = new QPushButton(this);
    this->buttonText->setText("Text animation");

    this->lineEditText = new QLineEdit(this);

    QHBoxLayout * textLayout = new QHBoxLayout();
    textLayout->addWidget(this->buttonText);
    textLayout->addWidget(this->lineEditText);

    this->verticalBox = new QVBoxLayout();
    this->verticalBox->addWidget(this->buttonMustacheAnimation);
    this->verticalBox->addLayout(textLayout);

    setLayout(this->verticalBox);
}

void Animation::control()
{
    connect(this->buttonMustacheAnimation, &QPushButton::clicked, this, &Animation::sloButtonMustacheAnimation);
    connect(this->buttonText, &QPushButton::clicked, this, &Animation::sloButtonTextAnimation);
}

void Animation::appearance()
{
    this->setStyleSheet("Animation {background : url(:/img/popupBack.jpg)}");
}
