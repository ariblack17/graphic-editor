#ifndef graphicViewController_h
#define graphicViewController_h

#include "ECGraphicViewImp.h"
#include "shapemodel.h"
//#include "keystrokeobserver.h"
#include "documentmodel.h"
#include <allegro5/allegro.h>
#include <iostream>
#include <vector>

// extension of ECGraphicViewImp <controller, extension of view>
class graphicViewController : public ECGraphicViewImp // <view>
{
public:
    graphicViewController(int width, int height, std::vector< std::vector<int> > &datain) : ECGraphicViewImp(width, height), data(datain) {
        mode = 0;                                                       // default mode = edit
        doc.insertNewData(data);                                        // for loading a save file
    }
    void changeMode();                                                  // must be public
    void changeInsertion();
    void changeShapeMode();
    void changeCtrlHeld();
    int getInsertion() { return insertionMode; }
    int getMode() { return mode; }
    int getShapeMode() { return shapeMode; }
    int getCtrlHeld() { return ctrlHeld; }
    void renderStart();
    void renderEnd() { al_flip_display(); }
    document doc;

private:
    bool mode;              // 0 (default?) for edit, 1 for insertion
    bool insertionMode;     // 0 for rectangle, 1 for ellipse
    bool shapeMode;         // 0 for line, 1 for filled
    bool ctrlHeld;          // to link mouse/key observers
    std::vector< std::vector<int> > data;
};

#endif /* graphicViewController_h */



