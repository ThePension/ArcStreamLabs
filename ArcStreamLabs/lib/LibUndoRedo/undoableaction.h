#pragma once

class UndoableAction
{
    public:
        virtual ~UndoableAction() = 0;
        void virtual execute() = 0;
        void virtual undo() = 0;
};
