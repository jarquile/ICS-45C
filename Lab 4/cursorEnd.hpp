#ifndef CURSOREND_HPP
#define CURSOREND_HPP

#include "Command.hpp"

class cursorEnd : public Command
{
public:
    virtual void execute(EditorModel& editor)
    {
        previous = editor.cursorColumn();
        editor.end();
    }

    virtual void undo(EditorModel& editor)
    {
        editor.moveColumn(previous);
    }

private:
    int previous;
};

#endif
