//
//  main.cpp
//  2048
//
//  Created by Chloé Yukino on 05/03/2019.
//  Copyright © 2019 Cyzu. All rights reserved.
//

//#include <iostream>
//#include <cstdint>

#include "game.h"

int main(int argc, const char * argv[]) {
    int init_game = init();
    
    if (init_game == 0) run();
    
    return 0;
}
