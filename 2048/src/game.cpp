//
//  game.cpp
//  2048
//
//  Created by Chloé Yukino on 05/03/2019.
//  Copyright © 2019 Cyzu. All rights reserved.
//

#include <cstdint>
#include <cstdio>
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>

#include <string>

#include "game.h"

WINDOW *window;

void write_score(int score){
    std::string str = "Score : " + std::to_string(score);
    mvaddstr(3, 5, str.c_str());
}

int init(){
    window = initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    
    // Enable function keys
    keypad(window, true);
    
    // Disable input blocking
    nodelay(window, true);
    
    // Hide cursor
    curs_set(0);
    
    if(!has_colors()) {
        endwin();
        printf("ERROR: Terminal does not support color.\n");
        exit(1);
    }
    // Enable color modification
    start_color();
    
    return 0;
}

void close(){
    endwin();
}

void run(){
    
    int input;
    int x = 5, y = 3;
    bool quit = false;
    int score = 0, tick = 0;
    
//    int x = 0, y = 0;
//    for (int i = 0; i < 20; i++) {
//        move(x, y);
//        write_text("x");
//        x++;
//    }
//
//    x = 0;
//    y = 0;
//    for (int i = 0; i < 20; i++) {
//        move(x, y);
//        write_text("y");
//        y++;
//    }
    
    
    while(1){
        input = wgetch(window);
        mvaddch(y, x, ' ');
        
        switch(input) {
            case 'q':
                quit = true;
                break;
            case KEY_UP:
            case 'e':
                y -= 1;
                break;
            case KEY_DOWN:
            case 'd':
                y += 1;
                break;
            case KEY_LEFT:
            case 's':
                x -= 1;
                break;
            case KEY_RIGHT:
            case 'f':
                x += 1;
                break;
            default:
                break;
        }
        if (quit == true) break;
        mvaddch(y, x, '$');
        
        if(tick % 30000 == 0) score ++;
        
        write_score(score);
//        usleep(100000); // 100 ms
        tick++;
        refresh();
    }
    
    close();
}
