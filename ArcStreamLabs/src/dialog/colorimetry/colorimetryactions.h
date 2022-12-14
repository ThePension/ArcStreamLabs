#pragma once

#include "../../undo_redo/undoableaction.h"

class QSlider;

class ColorimetryActions : public UndoableAction
{
    private:
        QSlider *** slidersTab;
        int **values;
        int **backup;

    public:
        ColorimetryActions(int **backup, int **values, QSlider *** slidersTab);
        ColorimetryActions(int **values, QSlider *** slidersTab);
        virtual ~ColorimetryActions() override;

        void execute() override;
        void undo()override;
};
