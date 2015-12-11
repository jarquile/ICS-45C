// InteractionProcessor.cpp
//
// ICS 45C Fall 2015
// Project #4: People Just Love to Play with Words
//
// Implementation of the InteractionProcessor class

#include "InteractionProcessor.hpp"
#include "EditorException.hpp"
#include "Interaction.hpp"
#include <stack>
#include <iostream>


// This function implements command execution, but does not handle "undo"l
// and "redo"; you'll need to add that handling.

void InteractionProcessor::run()
{
    std::stack<Interaction> undoStack;
    std::stack<Interaction> redoStack;
    
    view.refresh();

    while (true)
    {
        Interaction interaction = interactionReader.nextInteraction();

        if (interaction.type() == InteractionType::quit)
        {
            break;
        }
        else if (interaction.type() == InteractionType::undo)
        {
            
            if (!undoStack.empty())
            {
            

                Interaction undoInteraction = undoStack.top();
                Command* command = undoInteraction.command();
                try
                {
                    undoStack.pop();
                    redoStack.push(undoInteraction);
                    command->undo(model);
                    model.clearErrorMessage();
                }
                catch(EditorException& e)
                {

                    model.setErrorMessage(e.getReason());
                    delete command;
                }
                view.refresh();             
                
            }
        
        
        }
        else if (interaction.type() == InteractionType::redo)
        {
            if(!redoStack.empty())
            {
                Interaction redoInteraction = redoStack.top();
                Command* command = redoInteraction.command();
                try
                {

                    
                    redoStack.pop();
                    undoStack.push(redoInteraction);
                    command->execute(model);
                    model.clearErrorMessage();
                }

                
                catch(EditorException& e)
                {
                    model.setErrorMessage(e.getReason());
                    delete command;
                }
                view.refresh();
            }
        }
        else if (interaction.type() == InteractionType::command)
        {
            Command* command = interaction.command();

            try
            {
                command->execute(model);
                undoStack.push(interaction);
                model.clearErrorMessage();
            }
            catch (EditorException& e)
            {

                model.setErrorMessage(e.getReason());
                delete command;
            }

            view.refresh();

            // Note that you'll want to be more careful about when you delete
            // commands once you implement undo and redo.  For now, since
            // neither is implemented, I've just deleted it immediately
            // after executing it.  You'll need to wait to delete it until
            // you don't need it anymore.
            //delete command;
        }
    }

    while(!undoStack.empty())
    {
        Interaction undoInteraction = undoStack.top();
        delete undoInteraction.command();
        undoStack.pop();
    }
    while(!redoStack.empty())
    {
        Interaction redoInteraction = redoStack.top();
        delete redoInteraction.command();
        redoStack.pop();
    }
}

