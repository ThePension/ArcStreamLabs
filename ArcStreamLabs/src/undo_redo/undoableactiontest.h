#pragma once

#include "undoableaction.h"

class UndoableActionTest : public UndoableAction
{
    private:
        int backup;
        int newValue;
        int * value;

    public:
        UndoableActionTest(int newValue, int * value);
        virtual ~UndoableActionTest() override;

        void execute() override;
        void undo() override;
};

