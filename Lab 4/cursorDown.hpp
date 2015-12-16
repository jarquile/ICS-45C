#ifndef CURSORDOWN_HPP
#define CURSORDOWN_HPP

#include "Command.hpp"

class cursorDown : public Command
{
public:
    virtual void execute(EditorModel& editor)
    {
        column = editor.cursorColumn();
        editor.moveLine(editor.cursorLine() + 1);
    }

    virtual void undo(EditorModel& editor)
    {
        editor.moveLine(editor.cursorLine() - 1);
        editor.moveColumn(column);
    }
private:
    int column;
};

#endif
