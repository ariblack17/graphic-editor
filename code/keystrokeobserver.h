#ifndef keystrokeobserver_h
#define keystrokeobserver_h
#include "ECGraphicViewImp.h"
#include "graphicViewController.h"
#include "shapemodel.h"
#include <vector>
#include <allegro5/allegro.h>
#include <iostream>

// ECKeystrokeObserver <observer, controller?>
class observerKeystroke : public ECObserver
{
public:
    observerKeystroke(graphicViewController &viewIn);
    virtual void Update();
    //bool ctrlHeld() { return ctrlkey; }
private:
    graphicViewController &view;
    // true if pressed, false if not
    bool spacebar;
    bool zkey;
    bool ykey;
    bool dkey;
    bool gkey, fkey, ctrlkey;
    bool upkey, downkey, leftkey, rightkey;

};
#endif /* keystrokeobserver_h */
