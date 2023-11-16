//
//  Created by Yufeng Wu on 3/2/22.
//
#include "ECGraphicViewImp.h"

// Test graphical view code
int real_main(int argc, char **argv) {
    const int widthWin = 1000, heightWin = 1000;
    ECGraphicViewImp view(widthWin, heightWin);
    
    view.Show();
  
  
    return 0;
}

int main(int argc, char **argv) {
    return real_main(argc, argv);
    //return al_run_main(argc, argv, real_main);
}

