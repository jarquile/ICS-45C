#ifndef CURSORHOME_HPP
#define CURSORHOME_HPP

#include "Command.hpp"

class cursorHome : public Command
{
public:
    virtual void execute(EditorModel& editor)
    {
        previous = editor.cursorColumn();
        editor.home();
    }

    virtual void undo(EditorModel& editor)
    {
        editor.moveColumn(previous);
    }

private:
    int previous;
};

#endif
