// EditorModel.cpp
//
// ICS 45C Fall 2015
// Project #4: People Just Love to Play with Words
//
// Implementation of the EditorModel class

#include "EditorModel.hpp"
#include "EditorException.hpp"
#include "BooEditLog.hpp"

EditorModel::EditorModel()
	:currentLine{1},currentCol{1},error{""}
{
    data.push_back("");
}


int EditorModel::cursorLine() const
{
    return currentLine;
}


int EditorModel::cursorColumn() const
{
    return currentCol;
}


int EditorModel::lineCount() const
{
    return data.size();
}


const std::string& EditorModel::line(int lineNumber) const
{

    return data[(lineNumber - 1)];
}


const std::string& EditorModel::currentErrorMessage() const
{
    return error;
}


void EditorModel::setErrorMessage(const std::string& errorMessage)
{
    error=errorMessage;
}


void EditorModel::clearErrorMessage()
{
    error="";
}

void EditorModel::home()
{
    currentCol = 1;
}

void EditorModel::end()
{
    currentCol = line(currentLine).size() + 1;
}

char EditorModel::backspace()
{
    if (currentLine == 1 && currentCol == 1)
        throw EditorException("Already at Beginning");

    else if (currentCol != 1)
    {   
        char deleted = data[currentLine - 1][currentCol - 2];
        data[currentLine - 1].erase(currentCol - 2, 1);
        moveColumn(currentCol - 1);
        return deleted;
    }

    else
    {
        moveLine(currentLine - 1);
        end();
        data.erase(data.begin() + currentLine);
        return '\0';
    }
}

void EditorModel::moveLine(int newLine)
{
    if (newLine < 1)
        throw EditorException("Already at Top");
    else if (newLine > lineCount())
        throw EditorException("Already at Bottom");
    currentLine = newLine;
    if (currentCol > line(currentLine).size() + 1)
        currentCol = line(currentLine).size() + 1;
}


void EditorModel::moveColumn(int newColumn)
{
  
    if (newColumn < 1)
    {
        if (currentLine == 1)
            throw EditorException("Already at Begining");
        currentLine--;
        currentCol = line(currentLine).size() + 1;
    }
    else if (newColumn > line(currentLine).size() + 1)
    {
        if (currentLine + 1 > lineCount())
            throw EditorException("Already at End");
        currentLine++;
        currentCol = 1;
    }
    else
        currentCol = newColumn;
}

void EditorModel::insertChar(const char C)
{
    data[currentLine - 1].insert(currentCol - 1, 1,C);
    currentCol++;
}

void EditorModel::NewLine()
{
    data.insert(data.begin() + currentLine, ""); 
    if (currentCol - 1 < line(currentLine).size())
    {
        std::string temp =data[currentLine - 1].substr(currentCol - 1);
        data[currentLine] = temp;
        data[currentLine - 1] = data[currentLine - 1].erase(currentCol - 1, data[currentLine - 1].size());
    }
    moveLine(currentLine + 1);
    home();
}

void EditorModel::deleteLine()
{
    data.erase(data.begin() + currentLine - 1);
}


void EditorModel::deleteLineCheck()
{
    deleteLine();
    if (lineCount() == 0)
        data.push_back("");
    if (currentLine > lineCount())
       moveLine(currentLine - 1);
    if (currentCol > line(currentLine).size())
        end();
}

void EditorModel::insertLine(const std::string line)
{
    data[currentLine - 1] += line;
}