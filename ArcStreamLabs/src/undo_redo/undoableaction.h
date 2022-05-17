#pragma once

#include <QObject>

class UndoableAction : public QObject
{
    public:
        virtual ~UndoableAction() {};
        void virtual execute() = 0;
        void virtual undo() = 0;
};
