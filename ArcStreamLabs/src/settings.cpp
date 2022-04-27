#include "settings.h"

Settings::Settings(Colorimetry * colorDialog, Filter * filterDialog, SpecialEffect * specialEffectDialog, Animation * animationDialog, QWidget * parent)
    : QWidget(parent)
{
    this->colorDialog = colorDialog;
    this->filterDialog = filterDialog;
    this->specialEffectDialog = specialEffectDialog;
    this->animationDialog = animationDialog;
}

void Settings::readFile()
{
    QFile data(this->filename);
    if (data.open(QIODevice::ReadOnly))
    {
        try
        {
            QDataStream in(&data);

            // Read and check the header
            quint16 magic;
            in >> magic;
            if (magic != 0xCFDE)
            {
                QMessageBox::critical(this,"Erreur","BAD_FILE_FORMAT");
                return;// XXX_BAD_FILE_FORMAT;
            }

            // quint16 iconeSizeIn;
            // in >> iconeSizeIn;
            Mat colorimetryKernel = this->colorDialog->getKernel();
            for (int i = 0; i < this->colorDialog->getWidth(); i++)
            {
                for (int j = 0; j < this->colorDialog->getHeight(); j++)
                {
                    float sliderValue;
                    in >> sliderValue;
                    colorimetryKernel.at<float>(i, j) = sliderValue * 1000.0;
                }
            }

            this->colorDialog->setKernel(colorimetryKernel);
        }
        catch (Exception e)
        {
            QMessageBox::critical(this, "Erreur", "Fichier illisible");
        }

        data.close();
        this->colorDialog->update();
    }
    else
    {
        QMessageBox::critical(this, "Erreur", "Erreur d'ouverture\n" + filename);
        filename = "";
    }
}

void Settings::exportSettings()
{
    if (!this->filename.isEmpty())
    {
        QFile data(this->filename);

        if (!data.open(QFile::WriteOnly | QFile::Truncate))
        {
            QMessageBox::critical(this, "Erreur", "Erreur d'ouverture");
        }

        QDataStream out(&data);

        // Write a header with a "magic number" and a version
        out << static_cast<quint16>(0xCFDE);

        // TODO : Should be the number of settings/filters
        // out << static_cast<quint16>(this->getIconSize());

        Mat colorimetryKernel = this->colorDialog->getKernel();
        for (int i = 0; i < this->colorDialog->getWidth(); i++)
        {
            for (int j = 0; j < this->colorDialog->getHeight(); j++)
            {
                out << static_cast<float>(colorimetryKernel.at<float>(i, j));
            }
        }

        data.close();
    }
    else
    {
        exportSettingsAs();
    }
}

void Settings::exportSettingsAs()
{
    QString newFileName = QFileDialog::getSaveFileName(this, tr("Sauver"), "./", tr("Dessins (*.asls)"));
    if (!newFileName.isEmpty())
    {
        this->filename = newFileName;
        exportSettings();
    }
}

void Settings::importSettings()
{
    QString newFileName = QFileDialog::getOpenFileName(this, tr("Ouvrir"), "./", tr("Dessins (*.asls)"));
    if (!newFileName.isNull())
    {
        this->filename = newFileName;
        readFile();
    }
}
