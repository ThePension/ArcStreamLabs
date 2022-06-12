#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *labelInformation = new QLabel(this);
    QLabel *labelLogo = new QLabel(this);

    QPixmap pixmap(":/img/hearc.png");
    pixmap = pixmap.scaled(400, 200, Qt::KeepAspectRatio);
    labelLogo->setPixmap(pixmap);

    labelInformation->setText("ArcStreamLabs est un logiciel destiné aux streameurs.\n\nIl a été réalisé à la HE-Arc par les élèves suivants : \n - Alessio Comi\n - Nicolas Aubert\n - Théo Vuilliomenet\n");

    mainLayout->addWidget(labelInformation);
    mainLayout->addWidget(labelLogo);
}
