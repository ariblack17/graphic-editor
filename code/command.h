
#ifndef command_h
#define command_h
#include "ECGraphicViewImp.h"
#include <vector>
#include <allegro5/allegro.h>
#include <iostream>


// command class
 class command
 {
 public:
     virtual ~command() {}
     virtual void execute() = 0;
     virtual void reverse() = 0;
 };


// command history class
 class commandHist
 {
 public:
     commandHist();
     virtual ~commandHist();
     bool undo();
     bool redo();
     void executeCommand( command *pCmd );
     
 private:
     std::vector<command *> listUndoCommands;
     std::vector<command *> listRedoCommands;
     //int posCurrCmd;
 };



#endif /* command_h */
