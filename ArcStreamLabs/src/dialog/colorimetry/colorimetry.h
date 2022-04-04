#pragma once

#include <QDialog>
//#include <QTabWidget>
//#include <QDialogButtonBox>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class Colorimetry : public QDialog
{
    Q_OBJECT

    private:
        //QTabWidget *tabWidget;
        //QDialogButtonBox *buttonBox;

    public:
        Colorimetry(QWidget *parent = 0);

    signals:
        // TODO

    private slots:
        // TODO
};
