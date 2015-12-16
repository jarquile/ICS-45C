#ifndef NEWLINE_HPP
#define NEWLINE_HPP

#include "Command.hpp"

class newLine : public Command
{
public:
    virtual void execute(EditorModel& editor)
    {
        cursor = editor.cursorColumn();
        editor.NewLine();
    }

    virtual void undo(EditorModel& editor)
    {
        int currentLine = editor.cursorLine();
        editor.moveLine(--currentLine);
        editor.insertLine(editor.line(++currentLine));
        editor.moveLine(currentLine);
        editor.deleteLine();
        editor.moveLine(--currentLine);
        editor.moveColumn(cursor);
    }
private:
    int cursor;
};

#endif
