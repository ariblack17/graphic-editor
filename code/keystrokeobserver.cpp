#include "keystrokeobserver.h"
#include "allegro5/allegro_primitives.h"
#include <allegro5/allegro_image.h>
using namespace std;

observerKeystroke :: observerKeystroke( graphicViewController &viewIn ) : view(viewIn), spacebar(false), zkey(false), ykey(false), dkey(false) {
}

void observerKeystroke :: Update() {
    ECGVEventType evt = view.GetCurrEvent();
    // is the space bar released?
    if( evt == ECGV_EV_KEY_UP_SPACE) {
        spacebar = true;
    }
    // is the z key released?
    if( evt == ECGV_EV_KEY_UP_Z) {
        zkey = true;
    }
    // is the y key released?
    if( evt == ECGV_EV_KEY_UP_Y) {
        ykey = true;
    }
    // is the d key released?
    if( evt == ECGV_EV_KEY_UP_D) {
        dkey = true;
    }
    // is the g key released?
    if( evt == ECGV_EV_KEY_UP_G) {
        gkey = true;
    }
    // is the f key released?
    if( evt == ECGV_EV_KEY_UP_F) {
        fkey = true;
    }
    // is the ctrl key pressed?
    if( evt == ECGV_EV_KEY_DOWN_CTRL) {
        ctrlkey = true;
    }
    // is the ctrl key pressed?
    if( evt == ECGV_EV_KEY_UP_CTRL ) {
        ctrlkey = false;
    }
    // directional
    if( evt == ECGV_EV_KEY_UP_UP ) {
        upkey = true;
    }
    if( evt == ECGV_EV_KEY_UP_DOWN ) {
        downkey = true;
    }
    if( evt == ECGV_EV_KEY_UP_LEFT ) {
        leftkey = true;
    }
    if( evt == ECGV_EV_KEY_UP_RIGHT ) {
        rightkey = true;
    }
    
    // if this is the timer event
    if( evt == ECGV_EV_TIMER ) {
        if( spacebar ) {
            view.changeMode();
            spacebar = false;
        }
        if( zkey ) {
            cout << "undo" << endl;
            zkey = false;
        }
        if( ykey ) {
            cout << "redo" << endl;
            ykey = false;
        }
        if( dkey ) {
            view.doc.removeSelected();
            view.renderStart();
            view.renderEnd();
            dkey = false;
        }
        if ( gkey ) {
            view.changeInsertion();
            gkey = false;
        }
        if ( fkey ) {
            view.changeShapeMode();
            fkey = false;
        }
        if ( ctrlkey ) {
            if(!view.getCtrlHeld()) view.changeCtrlHeld();
        }
        if ( !ctrlkey ) {
            if(view.getCtrlHeld()) view.changeCtrlHeld();
        }
        // for up/down/left/right shape movement 
        int count = view.doc.getNumSelected();
        if(count > 0) {
            int index = 0;                                                                      // index at the moment
            int current = 0;                                                                    // current selected, count = total selected
            while(current < count) {                                                            // while we haven't yet seen all the selected shapes
                shape x = view.doc.accessShape(index);
                if (x.isSelected()) {                                                           // if this shape is selected
                    view.renderStart();
                    if( upkey ) {
                        if (x.getType() == 1) x.moveLR(x._x1, x._y1-10, x._x2, x._y2-10);       // check what type of shape is selected, call corresponding method
                        else x.moveEll(x._xcenter, x._ycenter-10);
                        view.doc.changeShape(index, x);                                         // update shape location info
                        upkey = false;
                    }
                    if( downkey ) {
                        if (x.getType() == 1) x.moveLR(x._x1, x._y1+10, x._x2, x._y2+10);
                        else x.moveEll(x._xcenter, x._ycenter+10);
                        view.doc.changeShape(index, x);
                        downkey = false;
                    }
                    if( leftkey ) {
                        //cout << "left" << endl;
                        if (x.getType() == 1) x.moveLR(x._x1-10, x._y1, x._x2-10, x._y2);
                        else x.moveEll(x._xcenter-10, x._ycenter);
                        view.doc.changeShape(index, x);
                        leftkey = false;
                    }
                    if( rightkey ) {
                        //cout << "right" << endl;
                        if (x.getType() == 1) x.moveLR(x._x1+10, x._y1, x._x2+10, x._y2);
                        else x.moveEll(x._xcenter+10, x._ycenter);
                        view.doc.changeShape(index, x);
                        rightkey = false;
                    }
                    current += 1;
                    view.renderEnd();
                }
                index += 1;
            }
        }
    }
}
