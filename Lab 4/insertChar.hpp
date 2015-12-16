#ifndef INSERTCHAR_HPP
#define INSERTCHAR_HPP

#include "Command.hpp"

class insertChar : public Command
{
public:
    insertChar(char C) : C{C}
    {
    }
    
    virtual void execute(EditorModel& editor)
    {
        editor.insertChar(C);
    }

    virtual void undo(EditorModel& editor)
    {
        editor.backspace();
    }
private:
    char C;
};

#endif
