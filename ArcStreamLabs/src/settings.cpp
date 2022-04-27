#include "settings.h"

Settings::Settings(Colorimetry * colorDialog, Filter * filterDialog, SpecialEffect * specialEffectDialog, Animation * animationDialog, QWidget * parent)
    : QWidget(parent)
{
    this->colorDialog = colorDialog;
    this->filterDialog = filterDialog;
    this->specialEffectDialog = specialEffectDialog;
    this->animationDialog = animationDialog;
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
                out << static_cast<float16_t>(colorimetryKernel.at<float>(i, j));
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
    QString newFileName = QFileDialog::getSaveFileName(this, tr("Sauver"), "./", tr("Dessins (*.icnqt)"));
    if (!newFileName.isEmpty())
    {
        this->filename = newFileName;
        exportSettings();
    }
}

void Settings::importSettings()
{

}
