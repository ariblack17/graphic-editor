#ifndef documentmodel_h
#define documentmodel_h
#include <vector>
#include <allegro5/allegro.h>
#include <iostream>
#include "shapemodel.h"
#include "ECGraphicViewImp.h"

// document <model>
class document
{
public:
    document() : numSelected(0) { }
    ~document() {
        data.clear();
//        data.push_back(std::vector<int>(listShapes.size()));            // first value = number of shapes
//        for(auto x : listShapes) {                                      // for each shape pair
//            std::vector<int> thisShape;                                 // init vector containing shape info
//            // find what type of shape
//            if(x.first.getType() == 1 && x.first.getFill() == 0) {      // unfilled rectangle
//                thisShape.push_back(0); // no fill
//                thisShape.push_back(4);
//                // push back coordinates, then color
//            }
//            if(x.first.getType() == 1 && x.first.getFill() == 1) {      // filled rectangle
//                thisShape.push_back(2); // fill
//                thisShape.push_back(4);
//                // push back coordinates, then color
//            }
//        }
        listShapes.clear();
        // insert data into document during destructor, as document closes
    }
    void addShape(shape &other) {
        std::pair<shape, bool> newshape = {other, 0};
        listShapes.push_back(newshape);
    }
    void removeShape(int i) { listShapes.erase(listShapes.begin() + i); }
    void removeSelected() {
        int i = 0;
        while(getNumSelected() > 0) {                       // while at least one shape is selected
            shape x = listShapes[i].first;
            if (listShapes[i].second == 1) {                // if this shape is selected
                listShapes.erase(listShapes.begin() + i);
                decreaseSelected();
            }
            i++;
        }
    }
    void unselectAll() {
        int i = 0;
        while(getNumSelected() > 0) {                       // while at least one shape is selected
            shape x = listShapes[i].first;
            if (listShapes[i].second == 1) {                // if this shape is selected
                listShapes[i].second = 0;                   // unselect
                decreaseSelected();                         // decrement selected count
                x.flipSelected();                           // update shape object attribute
                changeShape(i, x);
            }
            i++;
        }
    }
    // shape methods
    void changeShape(int i, shape &other) {                                 // for changing shape attributes
        listShapes[i].first = other;
        listShapes[i].second = other.isSelected();
    }
    shape accessShape(int i) const { return listShapes[i].first; }
    int getNumShapes() const { return listShapes.size(); }
    
    // for supporting multiple selection
    int getNumSelected() { return numSelected; }
    void increaseSelected() { numSelected += 1; }
    void decreaseSelected() { numSelected -= 1; }
    
    // for loading a previous save file
    void insertNewData(std::vector< std::vector<int> > &datain) {
        int x1, x2, y1, y2, temp;
        data = datain;
        int numShapes = data[0][0];                             // first line, first integer = number of shapes in document
        for (int i = 1; i <= numShapes; i++) {                  // extract info about each shape
            int shapeType = data[i][0];                         // second line, first integer = shape type
            // decide which shape to insert
            if (shapeType == 0 || shapeType == 2) {             // rectangle, filled rectangle
            // integers index 2-9 are bounding box
                x1 = data[i][2];
                y1 = data[i][3];
                if(data[i][4] == x1) x2 = data[i][6];
                else x2 = data[i][4];
                if(data[i][5] == y1) x2 = data[i][7];
                else x2 = data[i][5];
                // left = lower x   (top left = x1, y1)
                if(x1 > x2) { temp = x1; x1 = x2; x2 = temp; }  // need to find which is top left/bottom right
                // up = lower y
                if(y1 > y2) { temp = y1; y1 = y2; y2 = temp; }
                
                if(shapeType == 0) {
                    shape newRectangle(x1, x2, y1, y2, 1, 0);   // first const arg for rectangle default, second for fill
                    newRectangle.setColor(ECGV_BLACK);          // color defaults to black
                    addShape(newRectangle);
                }
                if(shapeType == 2) {
                    shape newRectangle(x1, x2, y1, y2, 1, 1);
                    newRectangle.setColor(ECGV_BLACK);
                    addShape(newRectangle);
                }
            }
            else if (shapeType == 1 || shapeType == 3) {        // ellipse, filled ellipse
                // integers index 1-2 center
                x1 = data[i][1];
                y1 = data[i][2];
                // integers index 3-4 x/y radii
                x2 = data[i][3];
                y2 = data[i][4];
                
                if(shapeType == 1) {
                    shape newEll(x1, y1, x2, y2, 0);            // const arg for fill
                    newEll.setColor(ECGV_BLACK);
                    addShape(newEll);
                }
                if(shapeType == 3) {
                    shape newEll(x1, y1, x2, y2, 1);
                    newEll.setColor(ECGV_BLACK);
                    addShape(newEll);
                }
            }
            else if (shapeType == 4) {  // composite shape
                // composite shape functionality here
            }
        }
    }

private:
    std::vector< std::pair<shape, bool> > listShapes;                   // keeps track of all shapes and their boolean selected status, 0: unselected 1: selected
    shape selectedShape;
    int numSelected;                                                    // keeps track of number of selected items
    std::vector< std::vector<int> > data;                               // shapes from save file
};

#endif /* documentmodel_h */
