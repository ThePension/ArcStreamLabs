#pragma once

#include <QDialog>

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class Filter : public QDialog
{
    Q_OBJECT

    private:
        QPushButton * buttonSepiaFilter;

        void geometry();
        void control();
        void appearance();

    public:
        Filter(QWidget *parent = 0);

    signals:
        void sigSetSepiaFilter();

    private slots:
        void sloButtonSepiaFilterClick();
};
