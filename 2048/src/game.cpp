//
//  game.cpp
//  2048
//
//  Created by Chloé Yukino on 05/03/2019.
//  Copyright © 2019 Cyzu. All rights reserved.
//

#include <cstdio>
#include <ncurses.h>

#include <string>
#include <fstream>

#include "game.h"
#include "../obj/Matrix.h"

WINDOW *window;
Matrix matrix;

int xmin = 5, ymin = 3;
int case_size_x = 6, case_size_y = 3;
int first_case_y = ymin+5+2, first_case_x = xmin+2;
int high_score;

void write_score(int score){
    std::string str = "Score : " + std::to_string(score);
    mvaddstr(ymin, xmin, str.c_str());
}

void write_high_score(int score){
    std::string str = "High score : " + std::to_string(score);
    mvaddstr(ymin+1, xmin, str.c_str());
}

void replace_hight_score(int score){
    std::ofstream file("doc/highScore", std::ofstream::trunc);
    if(file.is_open())
        file << score;
    file.close();
}

void draw_square(int size){
    int x, y;
    
    move(ymin+5, xmin);
    getyx(window, y, x);

    for (int i = 0; i <= size * case_size_y; i++) {
        
        if (i == 0){
            mvaddstr(y, xmin+1, "___________________________");
        }
        else if (i % 3 == 0){
             mvaddstr(y, xmin, "|______|______|______|______|");
        }
        else {
            mvaddstr(y, xmin, "|      |      |      |      |");
        }
        y++;
    }
}

void show_matrix(){
    int x = first_case_x, y = first_case_y;
    std::string str;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix.get(i, j) == 0) str = "    ";
            else str = std::to_string(matrix.get(i, j));
            
            mvaddstr(y, x, str.c_str());
            x += case_size_x+1;
        }
        x = first_case_x;
        y += case_size_y;
    }
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
    draw_square(4);
    
    file.close();
    return 0;
}

void close(){
    endwin();
}

void run(){
    
    int input;
    int x = xmin+30, y = ymin+30;
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
                //y -= 1;
                matrix.move_up();
                break;
            case KEY_DOWN:
            case 'd':
//                y += 1;
                matrix.move_down();
                break;
            case KEY_LEFT:
            case 's':
//                x -= 1;
                matrix.move_left();
                break;
            case KEY_RIGHT:
            case 'f':
//                x += 1;
                matrix.move_right();
                break;
            default:
                break;
        }
        if (quit == true) break;
        mvaddch(y, x, '$');
        
        show_matrix();
        
//        write_score(score);
//        usleep(100000); // 100 ms
        tick++;
        refresh();
    }
    if (score > high_score){
        replace_hight_score(score);
    }
        
    close();
}
