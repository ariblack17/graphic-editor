# graphic-editor
C++ basic graphic editor for in-class project; completed as UConn's CSE 3150 course's final project in Fall 2022. 

Note: code is not optimized and contains some bugs, but editor is functional.

## project specifications

### goals
The goal of this project was to, using Allegro5 and some skeleton starter code, develop a C++ program with a graphical user interface.
The result was a graphic editor, such that the user could draw and edit simple graphics (shapes). There was a specific emphasis on 
developing object-oriented code which follow a few design patterns, including 'model-view-controller', 'commands', and 'observers'.


### background
The project was split into two main parts, both of which contain a textfile write-up summarizing the implemented features, 
missing features, and known bugs.

The starter code provided a basic graphic user interface and a very brief outline of the expected structure of the program. 


### part 1
The first portion of the project defined the implementation of two modes: insertion and edit mode, such that the user could toggle
between the two modes using the space key. By default, the editor is in edit mode.

**Insertion mode** supports clicking and dragging the mouse to draw a rectangle upon release. The outline of the rectangle is visible as the 
mouse is dragged.

**Edit mode** supports selecting a shape by clicking on it, as well as the ability to move selected shapes with the mouse or deleting them
by pressing 'd'.

**Undo and redo** functionalities were also introduced, which allow the user to press 'z' to undo or 'y' to redo any action in either mode.


### part 2
The second part of the project added more functionalities to each of the implementations in part 1. 

For **insertion mode**, the user can now use 'g' to toggle between rectangle and ellipse insertion mode. They can also use 'f' to toggle
between filled and non-filled shapes. 

**Edit mode** now supports selection of multiple shapes (such that the user can press and hold 'ctrl' while clicking each desired shape), 
shape movement by keystrokes (such that the user can move selected shapes with the arrow keys), and grouping and ungrouping of shapes 
(such that users can select multiple shapes and use 'g' to group, or select a single grouped shape and use the same key to remove that
object from the group). 

Part 2 also saw the inclusion of **file save and load**; to save a file, we run the editor by passing a filename (ex: ./editor tmp.dat, for 
executable editor and save file tmp.dat). If the file already exists, the editor would load the previously saved graphics into the
editor and show those shapes stored in the file. The file is a text file, and is defined as follows: 
- the first line is a single integer n (the number of shapes in the file); each of the lines after the first specifies a single shape;
- rectangles are defined as 0 4 <coordinates of the bounding box> <color> (ex: 0 4 210 399 210 609 517 609 517 399 0);
- filled rectangles are the same with the first value swapped to 2 (ex: 2 4 210 399 210 609 517 609 517 399 0);
- ellipses are 1 <center coordinates> <x radius> <y radius> <color> (ex: 1 250 350 100 200 0);
- filled ellipses are the same with the first value swapped to 3;
- composite shapes have an integer following the first indicating its number of children, and each child is specified in a new line (ex: 4 2).
