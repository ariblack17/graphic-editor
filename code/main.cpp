#include "graphicViewController.h"            // current source files
#include "keystrokeobserver.h"
#include "mouseobserver.h"
#include <fstream>
#include <sstream>
#include <cstring>

int real_main(int argc, char **argv, std::vector< std::vector<int> > &data) {
    const int widthWin = 1200, heightWin = 1200;
    
    // initialize objects
    graphicViewController v(widthWin, heightWin, data);         // init view object, should work same as ECGraphicViewImp ?
    observerKeystroke keyOb(v);                                 // init keystroke observer
    observerMouse mouseOb(v);                                   // init mouse observer
    
    // attach observers
    v.Attach(&keyOb);                                           // attach key observer
    v.Attach(&mouseOb);                                         // attach mouse observer

    v.Show();                                                   // call main function
    
    return 0;
}

int main(int argc, char **argv) {
        
    std::string line;
    std::string filename = argv[1];
    std::ifstream myfile(filename);                             // ifstream object, myfile
    std::vector< std::vector<int> > data;
    // if file exists, open it
    if (myfile.is_open()) {
        while( getline( myfile, line ) ) {
            std::istringstream is( line );
            data.push_back(std::vector<int>( std::istream_iterator<int>(is), std::istream_iterator<int>()));
        }
        myfile.close();
    }
    // if file doesn't exist, create it and write to it
    else {
        // create new file
        std::ofstream outfile ("tmp.dat");                                                      // default name
        outfile << "1" << std::endl << "0 4 210 399 210 609 517 609 517 399 0" << std::endl;    // example code for master file
        outfile.close();
    }
    
    return real_main(argc, argv, data);
}
