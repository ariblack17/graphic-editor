#ifndef shapemodel_h
#define shapemodel_h
#include <cmath>
#include <allegro5/allegro.h>
#include <iostream>

enum shapetype {
    LINE = 0,
    RECTANGLE = 1,
    CIRCLE = 2,
    ELLIPSE = 3,
};

// shape <model>
class shape
{
public:
    // constructors for each shape
    shape() {}
    shape(int x1, int y1, int x2, int y2, int value, bool fill) : _x1(x1), _y1(y1), _x2(x2), _y2(y2), filled(fill) {
        if (value == 0) thisShapeType = LINE;
        else if (value == 1) thisShapeType = RECTANGLE;
    }
    shape(int xcenter, int ycenter, double radius, bool fill) : _xcenter(xcenter), _ycenter(ycenter), _radius(radius), filled(fill) {
        thisShapeType = CIRCLE;
    }
    shape(int xcenter, int ycenter, double radiusx, double radiusy, bool fill) : _xcenter(xcenter), _ycenter(ycenter), _radiusx(radiusx), _radiusy(radiusy), filled(fill) {
        thisShapeType = ELLIPSE;
    }
    // point comparison methods
    bool onLine(int x1, int y1) {
        if( (x1 <= fmax(_x1, _x2) ) && (x1 >= fmin(_x1, _x2))) {
            return ( (y1 <= fmin(_y1, _y2)) && (y1 >= fmax(_y1, _y2)) );
        }
        return false;
    }
    bool inRect(int x, int y) {
        return ((x <= _x1 && x >= _x2 && y >= _y1 && y <= _y2) ||
                (x <= _x2 && x >= _x1 && y >= _y1 && y <= _y2));
    }
    bool inCirc(int x1, int y1) {
        double dx = abs(x1 - _xcenter);
        double dy = abs(y1 - _ycenter);
        return (dx*dx + dy*dy <= _radius*_radius);
    }
    bool inEll(int x1, int y1) {
        double dx = (x1 - _xcenter) * (x1 - _xcenter);
        double dy = (y1 - _ycenter) * (y1 - _ycenter);
        return ((dx / (_radiusx * _radiusx)) + (dy / (_radiusy * _radiusy)) <= 1);
    }
    // attribute methods
    void moveLR(int a, int b, int c, int d) { _x1 = a, _y1 = b, _x2 = c, _y2 = d; }         // move coordinates of line/rectangle
    void moveEll(int a, int b) { _xcenter = a, _ycenter = b; }                              // move coordinates of ellipse
    shapetype getType() { return thisShapeType; }                                           // get type of shape
    
    bool isSelected() { return selected; }                                                  // check if selected
    void flipSelected() {                                                                   // select or unselect
        if(!selected) {setColor(ECGV_BLUE); }
        else setColor(baseColor);
        selected = !selected; }
    
    ECGVColor getColor() { return color; }                                                  // get color of shape
    void setColor(ECGVColor c) {                                                            // change color of shape
        if (!selected) {baseColor = color; }  // remember previous (base/normal) color
        color = c;                              // change to new color
    }
    bool getFill() const { return filled; }
    int getThickness() const { return thickness; }                                          // get thickness of line
    void setThickness(int t) { thickness = t; }                                             // change thickness of line
    // can make private and have accessor methods, but code would be significantly lengthier
    int _x1, _y1, _x2, _y2, _xcenter, _ycenter;
    double _radius, _radiusx, _radiusy;
    
    // for grouping
    int getGroup() const { return group; }
    void changeGroup(int i) { group = i; }
    
private:
    shapetype thisShapeType;
    bool selected = 0;
    bool filled;
    int thickness = 3;
    ECGVColor color = ECGV_BLACK;
    ECGVColor baseColor = ECGV_BLACK;
    
    int group = 0;                          // 0: no group, 1+: in group
};


#endif /* shapemodel_h */

