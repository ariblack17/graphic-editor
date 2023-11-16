#include "command.h"
#include "allegro5/allegro_primitives.h"
using namespace std;
 
commandHist :: commandHist() {
}
 
commandHist :: ~commandHist() {
    // clear undo list
    for(unsigned int i = 0; i < listUndoCommands.size(); i++) delete listUndoCommands[i];
    listUndoCommands.clear();
    // clear redo list
    for(unsigned int i = 0; i < listRedoCommands.size(); i++) delete listRedoCommands[i];
    listRedoCommands.clear();
}
 
bool commandHist :: undo() {
//    if(posCurrCmd < 0) return false;
//    listCommands[posCurrCmd]->reverse();
//    --posCurrCmd;
//    return true;
    if(listUndoCommands.size() == 0) return false;
    command* current = listUndoCommands.back();
    listUndoCommands.pop_back();
    current->reverse();
    listRedoCommands.push_back(current);
    return true;
}

bool commandHist :: redo() {
//    if(posCurrCmd >= (int)listCommands.size() - 1) return false;
//    ++posCurrCmd;
//    listCommands[posCurrCmd]->execute();
//    return true;
    if(listRedoCommands.size() == 0) return false;
    command* current = listRedoCommands.back();
    listRedoCommands.pop_back();
    current->reverse();
    listUndoCommands.push_back(current);
    return true;
}

void commandHist :: executeCommand(command *cmd) {
//    cmd->execute();
//    if( posCurrCmd >= -1 ){
//        int szList = listCommands.size();
//        for(unsigned int i = posCurrCmd + 1; i < szList; i++) {
//            delete listCommands.back();
//            listCommands.pop_back();
//        }
//    }
//    listCommands.push_back(cmd);
//    ++posCurrCmd;
    listUndoCommands.push_back(cmd);
    cmd->execute();
}
