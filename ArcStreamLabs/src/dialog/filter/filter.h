#pragma once

#include <QDialog>
#include "QBoxLayout"
#include "QVBoxLayout"
#include "sobelfilter.h"
#include "stylizationfilter.h"

class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;
class ArcStreamLab;

class Filter : public QDialog
{
    Q_OBJECT

    private:
        QVBoxLayout *verticalBox;

        QPushButton * buttonNoFilter;
        QPushButton * buttonSobelFilter; // Edge detector
        QPushButton * buttonStylizationFilter;
        ArcStreamLab *parent;
        QAction *actUndo, *actRedo;

        void geometry();
        void control();
        void appearance();

    public:
        Filter(QWidget *parent = 0);

    signals:
        void sigSetNoFilter();
        void sigSetSobelFilter(FilterActions *);
        void sigSetStylizationFilter(FilterActions *);

    private slots:
        void sloButtonNoFilter();
        void sloButtonSobelFilter();
        void sloButtonStylizationFilter();
};
