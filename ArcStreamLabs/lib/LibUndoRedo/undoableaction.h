#pragma once

class UndoableAction
{
    public:
        virtual ~UndoableAction();
        void virtual execute() = 0;
        void virtual undo() = 0;
};
