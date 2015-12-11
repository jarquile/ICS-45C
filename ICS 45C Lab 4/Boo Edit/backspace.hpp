#ifndef BACKSPACE_HPP
#define BACKSPACE_HPP

#include "Command.hpp"

class backspace : public Command
{
public:
    virtual void execute(EditorModel& editor)
    {
        C = editor.backspace();
    }

    virtual void undo(EditorModel& editor)
    {
        if (C == '\0')
            editor.NewLine();
        else
            editor.insertChar(C);
        
    }

private:
    char C;
};

#endif
