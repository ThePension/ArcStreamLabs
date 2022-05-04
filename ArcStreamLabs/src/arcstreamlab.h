#pragma once

#include <QtWidgets>

#include "dialog/colorimetry/colorimetry.h"
#include "dialog/filter/filter.h"
#include "dialog/specialEffect/specialeffect.h"
#include "dialog/animation/animation.h"
#include "settings.h"
#include "videostream.h"
#include "lib/LibCircularBuffer/libcircularbuffer_1.h"
#include "imageprocessing.h"
#include "LibUndoRedo/actionmanager.h"


class ArcStreamLab : public QWidget
{
    Q_OBJECT

    private:
        ActionManager *actionManager;

        VideoStream *rawStream;
        ImageProcessing *processedStream;

        CircularBuffer *circularBuffer;

        QGraphicsPixmapItem inputPixmap;
        QGraphicsPixmapItem outputPixmap;

        QHBoxLayout *buttonsHLayout; // Contains the play, pause and stop buttons
        QHBoxLayout *settingsHLayout; // Contains the Colorimetry, Filter, Special Effect and Animation blocs

        QVBoxLayout *colorimetryVLayout;
        QVBoxLayout *filterVLayout;
        QVBoxLayout *specialEffectVLayout;
        QVBoxLayout *animationVLayout;
        QVBoxLayout *videoInputVLayout; // Contains the camera raw input (little graphicsView) and all the buttons (play, pause, stop and snapshot)
        QVBoxLayout *mainVLayout;

        QGridLayout *displayGridLayout; // Contains the two graphics view and the buttons (all the display part)

        QGraphicsView *graphicViewInput; // Display the camera's raw input (little graphicsView)
        QGraphicsView *graphicViewProcess; // Dispaly the processed video (big graphicsView)

        QPushButton *btnPlay;
        QPushButton *btnPause;
        QPushButton *btnStop;
        QPushButton *btnSnapshot;

        QPushButton *btnColor; // Open the colorimetry dialog
        QPushButton *btnFilter; // Open the filter dialog
        QPushButton *btnSpecialEffect; // Open the special effect dialog
        QPushButton *btnAnimation; // Open the animation dialog

        // Label use as separator line
        QLabel *lblVSeparator;
        QLabel *lblHSeparator1;
        QLabel *lblHSeparator2;
        QLabel *lblHSeparator3;

        // Dialogs
        Colorimetry * colorDialog;
        Filter * filterDialog;
        SpecialEffect *specialEffectDialog;
        Animation *animationDialog;

        // The dimensions of the graphicsView
        float formatWidth = 16.0;
        float formatHeight = 9.0;

        // Settings
        Settings * settings;

    public:
        ArcStreamLab(QWidget *parent=nullptr);

        void responsiveResize();
        Settings * getSettings();

    private:
        void createUIGeometry(); // Create every UI's items and display it
        void createUIAppearance(); // Manage the appearance of the UI
        void createUIControl(); // Connect the UI's items to slots
        void imageButtons(); // Replace the buttons by images

    public slots:
        void sloUpdateRawStreamValue();
        void sloUpdateProcessedStreamValue();
        void sloUpdateColorimetryValues();
        void sloPlayButtonClicked();
        void sloPauseButtonClicked();
        void sloStopButtonClicked();
        void undo();
        void redo();
        void sloSaveSnapshot();
        void sloCreateFilterAction(FilterActions *);

};
