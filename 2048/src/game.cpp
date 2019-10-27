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
            if (matrix.get_pow(i, j) <= 1) str = "    ";
            else str = std::to_string(matrix.get_pow(i, j));
            
            switch (str.length()) {
                case 1:
                    str += "   ";      // Add 3 spaces
                    break;
                case 2:
                    str += "  ";       // Add 2 spaces
                    break;
                case 3:
                    str += " ";        // Add one space
                    break;
                default:
                    break;
            }
            
            mvaddstr(y, x, str.c_str());
            x += case_size_x+1;
        }
        x = first_case_x;
        y += case_size_y;
    }
}

void draw_start(){
    mvaddstr(11, 40, " _____   ______    ____    _____    _____");
    mvaddstr(12, 40, "|  ___| |__  __| / ___ \\  |  __  \\ |__ __|");
    mvaddstr(13, 40, "| |___    | |   | |   | | | |__| |   | |");
    mvaddstr(14, 40, "|___  |   | |   | |___| | |  __  /   | |");
    mvaddstr(15, 40, " ___| |   | |   |  ___  | | |  \\ \\   | |");
    mvaddstr(16, 40, "|_____|   |_|   |_|   |_| |_|   \\_\\  |_|");
    
    mvaddstr(19, 40, "Press up, down, left or right arrow to begin.");
    mvaddstr(20, 40, "Good luck !");
}

void draw_game_over(){
    mvaddstr(8, 40, "  _____     _____    _     _   ____");
    mvaddstr(9, 40, " /  ___|   / ___ \\  | \\   / | |  __|");
    mvaddstr(10, 40, "| |  ___  | |   | | |  \\_/  | | |__");
    mvaddstr(11, 40, "| | |_  | | |___| | | |\\ /| | |  __|");
    mvaddstr(12, 40, "| |___| | |  ___  | | |   | | | |__");
    mvaddstr(13, 40, " \\_____/  |_|   |_| |_|   |_| |____|");
    
    mvaddstr(14, 40, "  _____    _     _   ____   _____");
    mvaddstr(15, 40, " / ___ \\  | |   | | |  __| |  __  \\");
    mvaddstr(16, 40, "| |   | | | |   | | | |__  | |__|  |");
    mvaddstr(17, 40, "| |   | | \\ \\  / /  |  __| |  __  /");
    mvaddstr(18, 40, "| |___| |  \\ \\/ /   | |__  | |  \\ \\");
    mvaddstr(19, 40, " \\_____/    \\__/    |____| |_|   \\_\\");
}

void draw_no_move(){
     mvaddstr(14, 40, "There is no move possible toward this side...");
}

void write_help(){
    mvaddstr(30, xmin, "Press 'q' anytime to quit the game.");
    mvaddstr(31, xmin, "Press 'r' anytime to restart the game.");
    mvaddstr(43, xmin, "Copyright © 2019 Cyzu. All rights reserved.");
}


void delete_message(){
    for (int i = 8; i < 21; i++) {
        mvaddstr(i, 40, "                                                          ");
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
    bool quit = false, restart = false;
    
    write_help();
    draw_start();
    matrix.new_number();
    
    while(1){
        input = wgetch(window);
        
        switch(input) {
            case 'q':
                quit = true;
                break;
            case 'r':
                restart = true;
                break;
            case KEY_UP:
            case 'e':
                matrix.move_up();
                if (movement) {
                    matrix.new_number();
                    movement = false;
                    delete_message();
                }
                else draw_no_move();
                
                break;
            case KEY_DOWN:
            case 'd':
                matrix.move_down();
                if (movement) {
                    matrix.new_number();
                    movement = false;
                    delete_message();
                }
                else draw_no_move();
                break;
            case KEY_LEFT:
            case 's':
                matrix.move_left();
                if (movement) {
                    matrix.new_number();
                    movement = false;
                    delete_message();
                }
                else draw_no_move();;
                break;
            case KEY_RIGHT:
            case 'f':
                matrix.move_right();
                if (movement) {
                    matrix.new_number();
                    movement = false;
                    delete_message();
                }
                else draw_no_move();
                break;
            default:
                break;
        }
        if (quit) break;
        if (matrix.is_fully()) draw_game_over();
        if (restart){
            quit = false;
            restart = false;
            score = 0;
            
            delete_message();
            matrix.init_matrix();
            draw_start();
            matrix.new_number();
        }
        show_matrix();
        write_score(score);
        
        refresh();
    }
    if (score > high_score){
        replace_hight_score(score);
    }
        
    close();
}
