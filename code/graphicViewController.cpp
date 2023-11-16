#include "graphicViewController.h"
#include "allegro5/allegro_primitives.h"
#include <allegro5/allegro_image.h>

using namespace std;

// controller
void graphicViewController :: changeMode() {
    // changes mode if spacebar is pressed
    mode = !mode;   // 0: edit mode, 1: insertion mode
}
void graphicViewController :: changeCtrlHeld() {
    ctrlHeld = !ctrlHeld;
}
void graphicViewController :: changeInsertion() { insertionMode = !insertionMode; }

void graphicViewController :: changeShapeMode() { shapeMode = !shapeMode; }

// view extension
void graphicViewController :: renderStart() {
    al_clear_to_color(al_map_rgb(255,255,255));
    // redraw all shapes
    for(int i = 0; i < doc.getNumShapes(); i++) {                               // for each shape in the doc
        shape x = doc.accessShape(i);
//        if (x.getType() == 0) DrawLine(x._x1, x._y1, x._x2, x._y2, x.getThickness(), x.getColor());
        if (x.getType() == 1) { if (x.getFill() == 1) DrawFilledRectangle(x._x1, x._y1, x._x2, x._y2, x.getColor()); else
            DrawRectangle(x._x1, x._y1, x._x2, x._y2, x.getThickness(), x.getColor()); }   // color not changed
//        if (x.getType() == 2) DrawCircle(x._xcenter, x._ycenter, x._radius, x.getThickness(), x.getColor());
        if (x.getType() == 3) { if (x.getFill() == 1) DrawFilledEllipse(x._xcenter, x._ycenter, x._radiusx, x._radiusy, x.getColor()); else
            DrawEllipse(x._xcenter, x._ycenter, x._radiusx, x._radiusy, x.getThickness(), x.getColor()); }

    }
}
 
