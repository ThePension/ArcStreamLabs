#pragma once

#include <QDialog>
#include "QBoxLayout"
#include "QVBoxLayout"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class Filter : public QDialog
{
    Q_OBJECT

    private:
        QVBoxLayout *verticalBox;

        QPushButton * buttonDefaultFilter;
        QPushButton * buttonRedFilter;
        QPushButton * buttonGreenFilter;
        QPushButton * buttonBlueFilter;
        QPushButton * buttonSepiaFilter;
        QPushButton * buttonBlackAndWhiteFilter;

        void geometry();
        void control();
        void appearance();

    public:
        Filter(QWidget *parent = 0);

    signals:
        void sigSetDefaultFilter();
        void sigSetRedFilter();
        void sigSetGreenFilter();
        void sigSetBlueFilter();
        void sigSetSepiaFilter();
        void sigSetBlackAndWhiteFilter();

    private slots:
        void sloButtonDefaultFilterClick();
        void sloButtonRedFilterClick();
        void sloButtonGreenFilterClick();
        void sloButtonBlueFilterClick();
        void sloButtonSepiaFilterClick();
        void sloButtonBlackAndWhiteFilterClick();
};
