#include "mouseobserver.h"
#include "allegro5/allegro_primitives.h"
#include <allegro5/allegro_image.h>
using namespace std;

observerMouse :: observerMouse(graphicViewController &viewIn) : view(viewIn), cx(0), cy(0), cxDown(0), cyDown(0), cxUp(0), cyUp(0) {
}
void observerMouse :: Update() {
    ECGVEventType evt = view.GetCurrEvent();
    view.GetCursorPosition(cx, cy);
    bool changeshape;
    int ax1, ax2, ay1, ay2;
    // mouse down
    if(evt == ECGV_EV_MOUSE_BUTTON_DOWN) {
        cxDown = cx;
        cyDown = cy;
        click = true;
    }
    // mouse up
    if(evt == ECGV_EV_MOUSE_BUTTON_UP) {
        cxUp = cx;
        cyUp = cy;
        click = false;
        // selection
        if(view.getMode() == 0) {                                                           // triggers only in edit mode
            // check if point is inside shape
            if (firstclick && view.getCtrlHeld() == false) firstclick = !firstclick;        // flip firstclick if single shape
            for(int i = 0; i < view.doc.getNumShapes(); i++) {                              // for each shape in the doc
                shape x = view.doc.accessShape(i);
                // use shape equations to check if inside each shape type
                if(x.getType() == 0) inside = x.onLine(cx, cy);
                if(x.getType() == 1) inside = x.inRect(cx, cy);
                if(x.getType() == 2) inside = x.inCirc(cx, cy);
                if(x.getType() == 3) {inside = x.inEll(cx, cy);}
                // if point is inside, select the shape
                if(inside == true) {
                    if(x.isSelected() == false) {                                           // if clicked shape is not selected
                        int count = view.doc.getNumSelected();
                        if(count > 0) {
                            // if ctrl is not being held, remove old selected shapes
                            if (view.getCtrlHeld() == false) {
                                view.doc.unselectAll();
                            }
                        }
                        x.flipSelected();
                        view.doc.increaseSelected();
                        view.doc.changeShape(i, x);
                        firstclick = true;
                    }
                    break;
                }
            }
        }
        // unselection
        if(view.getMode() == 0) {
                int count = view.doc.getNumSelected();
                if(count > 0) {
                if(firstclick == false && dragging == false) {              // if i) a shape is selected and ii) you're clicking on it for the second time
                    int i = 0;
                    while(count <= view.doc.getNumSelected()) {             // while at least one shape is selected
                        shape x = view.doc.accessShape(i);
                        if (x.isSelected() == 1) {                          // if this shape is selected
                            x.flipSelected();                               // unselect the shape
                            view.doc.changeShape(i, x);
                            view.doc.decreaseSelected();
                            count++;
                        }
                        i++;
                    }
                }
            }
        }
                               
        // dragging shape
        if(dragging == true) {
            int count = 0;
            int i = 0;
            if(view.doc.getNumSelected() > 0) {                             // if at least one shape is selected
                while(count < view.doc.getNumSelected()) {                  // while at least one shape is selected
                    shape x = view.doc.accessShape(i);
                    if (x.isSelected() == 1) {                              // if this shape is selected
                        // check if shape is rectangle or ellipse
                        if (x.getType() == 1) x.moveLR(x._x1-(cxDown-cxUp), x._y1-(cyDown-cyUp), x._x2-(cxDown-cxUp), x._y2-(cyDown-cyUp));
                        else x.moveEll(x._xcenter-(cxDown-cx), x._ycenter-(cyDown-cy));
                        x.flipSelected();                                   // unselect the shape
                        view.doc.changeShape(i, x);
                        view.doc.decreaseSelected();
                        count++;
                    }
                    i++;
                }
            }
        }
        
        // adding/drawing new shape
        if(view.getMode() == 1) {                                                               // triggers only in insertion mode
            // check if rectangle
            if(view.getInsertion() == 0) {                                                      // if rectangle mode
                shape newRectangle(cxDown, cyDown, cxUp, cyUp, 1, view.getShapeMode());         // create new rectangle
                view.doc.addShape(newRectangle);                                                // add shape to document
            }
            else if (view.getInsertion() == 1) {                                                // if ellipse mode
                double xcenter = (cxDown + cxUp) / 2;
                double ycenter = (cyDown + cyUp) / 2;
                double radiusx = abs(cxDown - cxUp) / 2;
                double radiusy = abs(cyDown - cyUp) / 2;
                shape newEllipse(xcenter, ycenter, radiusx, radiusy, view.getShapeMode());      // create new ellipse
                view.doc.addShape(newEllipse);                                                  // add shape to document
                cout << "new shape selected?: " << newEllipse.isSelected() << endl;
            }
        }
        redraw = true;
        dragging = false;
    }
    
    // mouse moving
    if(evt == ECGV_EV_MOUSE_MOVING) {
        if (view.getMode() == 0) {                                                              // if in edit mode
            if (click == true && view.doc.getNumSelected() > 0) {                               // if clicking and smth is selected
                dragging = true;
                // get shape initial info
                int count = 0;
                int i = 0;
                while(count < view.doc.getNumSelected()) {                                      // while at least one shape is selected
                    shape x = view.doc.accessShape(i);
                    if (x.isSelected() == 1) {                                                  // if this shape is selected
                        // for line and rectangle
                        if(x.getType() == 1) {
                            ax1 = x._x1-(cxDown-cx);
                            ay1 = x._y1-(cyDown-cy);
                            ax2 = x._x2-(cxDown-cx);
                            ay2 = x._y2-(cyDown-cy);
                            view.renderStart();
                            view.DrawRectangle(ax1, ay1, ax2, ay2, ECGV_BLUE);
                            view.renderEnd();
                            // redraw on upclick
                        }
                        // for circle and ellipse
                        if(x.getType() == 3) {
                            // xcenter, ycenter, radiusx, radiusy
                            double ax = x._xcenter-(cxDown-cx);
                            double ay = x._ycenter-(cyDown-cy);
                            view.renderStart();
                            view.DrawEllipse(ax, ay, x._radiusx, x._radiusy, ECGV_BLUE);
                            view.renderEnd();
                            // redraw on upclick
                        }
                        count++;
                    }
                    i++;
                }
            }
        }
        // dragging "sketch" selection rectangle
        if (click == true && view.getMode() == 1) {
            view.renderStart();
            view.DrawRectangle(cxDown, cyDown, cx, cy);
            view.renderEnd();
        }
    }
    // timer event
    if( evt == ECGV_EV_TIMER) {
        if( redraw ) {
            view.renderStart();
            view.renderEnd();
            redraw = false;
            cxDown = -100;
            cyDown = -100;
        }
    }
}
