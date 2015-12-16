#ifndef CURSORLEFT_HPP
#define CURSORLEFT_HPP

#include "Command.hpp"

class cursorLeft : public Command
{
public:
    virtual void execute(EditorModel& editor)
    {
        editor.moveColumn(editor.cursorColumn() - 1);
    }

    virtual void undo(EditorModel& editor)
    {
        editor.moveColumn(editor.cursorColumn() + 1);
    }
};

#endif
