#ifndef CURSORRIGHT_HPP
#define CURSORRIGHT_HPP

#include "Command.hpp"

class cursorRight : public Command
{
public:
    virtual void execute(EditorModel& editor)
    {
        editor.moveColumn(editor.cursorColumn() + 1);
    }

    virtual void undo(EditorModel& editor)
    {
        editor.moveColumn(editor.cursorColumn() - 1);
    }
};

#endif
