//
//  game.cpp
//  2048
//
//  Created by Chloé Yukino on 05/03/2019.
//  Copyright © 2019 Cyzu. All rights reserved.
//

//#include <cstdint>
#include <cstdio>
//#include <unistd.h>
#include <ncurses.h>
//#include <stdlib.h>

#include <string>
#include <fstream>

#include "game.h"

WINDOW *window;
int xmin = 5, ymin = 3;
int high_score;

void write_score(int score){
    std::string str = "Score : " + std::to_string(score);
    mvaddstr(ymin, xmin, str.c_str());
}

void write_high_score(int score){
    std::string str = "High score : " + std::to_string(score);
    mvaddstr(ymin+2, xmin, str.c_str());
}

void replace_hight_score(int score){
    std::ofstream file("doc/highScore", std::ofstream::trunc);
    if(file.is_open())
        file << score;
    file.close();
}

int init(){
    int score;
    std::ifstream file("doc/highScore");
    
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
    
    if (file.is_open()){
        file >> score;
        high_score = score;
        write_high_score(score);
    }
    write_score(0);
    
    file.close();
    return 0;
}

void close(){
    endwin();
}

void run(){
    
    int input;
    int x = xmin+10, y = ymin+10;
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
        
//        write_score(score);
//        usleep(100000); // 100 ms
        tick++;
        refresh();
    }
    if (score > high_score){
        printf("high score modifié\n");
        replace_hight_score(score);
    }
        
    close();
}
