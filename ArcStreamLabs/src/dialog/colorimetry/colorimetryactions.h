#pragma once

#include "LibUndoRedo/undoableaction.h"

class QSlider;

class ColorimetryActions : public UndoableAction
{
    private:
        QSlider *** slidersTab;
        int **values;
        int **backup;

    public:
        ColorimetryActions(int **values, QSlider *** slidersTab);
        virtual ~ColorimetryActions() override;

        void execute() override;
        void undo()override;
};
