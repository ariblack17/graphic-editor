#ifndef mouseobserver_h
#define mouseobserver_h
#include "ECGraphicViewImp.h"
#include "graphicViewController.h"
#include "shapemodel.h"
#include "keystrokeobserver.h"
#include <vector>
#include <allegro5/allegro.h>
#include <iostream>

// ECMouseEvtObserver <observer>
class observerMouse : public ECObserver
{
public:
    observerMouse(graphicViewController &viewIn);
    virtual void Update();
private:
    // true if pressed, false if not
    graphicViewController &view;
    int cx, cy, cxDown, cyDown, cxUp, cyUp;     // cursor
    bool click;
    bool inside;
    bool redraw;                                // like fRedraw in given files, but that variable is private :/
    bool firstclick = false;
    bool dragging = false;
};
#endif /* mouseobserver_h */
