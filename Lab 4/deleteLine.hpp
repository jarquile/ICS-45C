#ifndef DELETELINE_HPP
#define DELETELINE_HPP

#include "Command.hpp"

class deleteLine : public Command
{
public:
    virtual void execute(EditorModel& editor)
    {
        position = editor.cursorColumn(); 
        deleted = editor.line(editor.cursorLine());
        editor.deleteLineCheck();
    }

    virtual void undo(EditorModel& editor)
    {
        if (editor.cursorLine() != 1 || editor.line(1) != "")
        {
            editor.end();
            editor.NewLine();
        }
        editor.insertLine(deleted);
        editor.moveColumn(position);
    }
private:
    int position;
    std::string deleted;
};

#endif
