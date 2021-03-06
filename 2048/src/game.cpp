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

#define NONE    -1
#define RIGHT   0
#define LEFT    1
#define DOWN    2
#define UP      3


WINDOW *window;
Matrix matrix;

int xmin = 5, ymin = 3;
int case_size_x = 6, case_size_y = 3;
int first_case_y = ymin+5+2, first_case_x = xmin+2;
int high_score;
bool game_over = false, quit = false, restart = false;

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
    int x = first_case_x, y = first_case_y, color = 0;
    std::string str;
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (matrix.get_pow(i, j) <= 1) str = "    ";
            else {
                str = std::to_string(matrix.get_pow(i, j));
                color = matrix.get(i, j);
            }
            
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
            attron(COLOR_PAIR(color+1));
            mvaddstr(y, x, str.c_str());
            attroff(COLOR_PAIR(color+1));
            
            x += case_size_x+1;
        }
        x = first_case_x;
        y += case_size_y;
    }
}

void draw_start(){
    mvaddstr(8, 40, " _____   ______    ____    _____    _____                 ");
    mvaddstr(9, 40, "|  ___| |__  __| / ___ \\  |  __  \\ |__ __|                 ");
    mvaddstr(10, 40, "| |___    | |   | |   | | | |__| |   | |                 ");
    mvaddstr(11, 40, "|___  |   | |   | |___| | |  __  /   | |                 ");
    mvaddstr(12, 40, " ___| |   | |   |  ___  | | |  \\ \\   | |                 ");
    mvaddstr(13, 40, "|_____|   |_|   |_|   |_| |_|   \\_\\  |_|                 ");
    
    mvaddstr(17, 45, "            ^");
    mvaddstr(18, 45, "Press   <       >   to begin and move numbers.");
    mvaddstr(19, 45, "            v");
    mvaddstr(21, 45, "Good luck !");
}

void draw_game_over(){
    mvaddstr(8, 40, "  _____     _____    _     _   ____                    ");
    mvaddstr(9, 40, " /  ___|   / ___ \\  | \\   / | |  __|                 ");
    mvaddstr(10, 40, "| |  ___  | |   | | |  \\_/  | | |__                 ");
    mvaddstr(11, 40, "| | |_  | | |___| | | |\\ /| | |  __|                 ");
    mvaddstr(12, 40, "| |___| | |  ___  | | |   | | | |__                 ");
    mvaddstr(13, 40, " \\_____/  |_|   |_| |_|   |_| |____|                 ");
    
    mvaddstr(14, 40, "  _____    _     _   ____   _____                 ");
    mvaddstr(15, 40, " / ___ \\  | |   | | |  __| |  __  \\                 ");
    mvaddstr(16, 40, "| |   | | | |   | | | |__  | |__|  |                 ");
    mvaddstr(17, 40, "| |   | | \\ \\  / /  |  __| |  __  /                 ");
    mvaddstr(18, 40, "| |___| |  \\ \\/ /   | |__  | |  \\ \\                 ");
    mvaddstr(19, 40, " \\_____/    \\__/    |____| |_|   \\_\\                 ");
    
    mvaddstr(21, 45, "Please press 'q' to quit or 'r' to restart a new game !");
}

void draw_no_move(){
     delete_message();
     mvaddstr(14, 45, "There is no move possible toward this side...");
}

void draw_arrows(int direction){
    int x = xmin + 10;
    int y = ymin + 20;
    switch (direction) {
        case 0:
            mvaddstr(y, x+4, "^");
            mvaddstr(y+1, x, "<");
            attron(A_BOLD);
            mvaddstr(y+1, x+8, ">");
            attroff(A_BOLD);
            mvaddstr(y+2, x+4, "v");
            break;
        case 1:
            mvaddstr(y, x+4, "^");
            attron(A_BOLD);
            mvaddstr(y+1, x, "<");
            attroff(A_BOLD);
            mvaddstr(y+1, x+8, ">");
            mvaddstr(y+2, x+4, "v");
            break;
        case 2:
            mvaddstr(y, x+4, "^");
            mvaddstr(y+1, x, "<");
            mvaddstr(y+1, x+8, ">");
            attron(A_BOLD);
            mvaddstr(y+2, x+4, "v");
            attroff(A_BOLD);
            break;
        case 3:
            attron(A_BOLD);
            mvaddstr(y, x+4, "^");
            attroff(A_BOLD);
            mvaddstr(y+1, x, "<");
            mvaddstr(y+1, x+8, ">");
            mvaddstr(y+2, x+4, "v");
            break;
        default:
            mvaddstr(y, x+4, "^");
            mvaddstr(y+1, x, "<");
            mvaddstr(y+1, x+8, ">");
            mvaddstr(y+2, x+4, "v");
            break;
    }
}


void delete_message(){
    for (int i = 8; i < 23; i++) {
        mvaddstr(i, 40, "                                                          ");
    }
}

void create_pairs(){
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    
    init_pair(2, 25, COLOR_BLACK);
    init_pair(3, 30, COLOR_BLACK);
    init_pair(4, 35, COLOR_BLACK);
    init_pair(5, 43, COLOR_BLACK);
    init_pair(6, 48, COLOR_BLACK);
    init_pair(7, 46, COLOR_BLACK);
    init_pair(8, 118, COLOR_BLACK);
    init_pair(9, 154, COLOR_BLACK);
    init_pair(10, 220, COLOR_BLACK);
    init_pair(11, 256, COLOR_BLACK);
    init_pair(12, 184, COLOR_BLACK);
    init_pair(13, 208, COLOR_BLACK);
    init_pair(14, 203, COLOR_BLACK);
    init_pair(15, 169, COLOR_BLACK);
    init_pair(16, 164, COLOR_BLACK);
    init_pair(17, 160, COLOR_BLACK);
}

int popup(char state){
    WINDOW *popup = newwin(5, 50, 21, 40);
    box(popup, '|', '-');
    
    if (state == 'q') mvwaddstr(popup, 1, 10, "Do you want to quit the game ?");
    else mvwaddstr(popup, 1, 10, "Do you want to restart a new game ?");
    
    mvwaddstr(popup, 3, 11, "Yes [y]              No [n]");
    wrefresh(popup);
    
    int input_key = wgetch(popup);
    if (input_key == 'y' || input_key == 'Y' || input_key == 'o' || input_key == 'O') {
        if (state == 'q'){ // le joueur veut quitter
            return -1;
        }
        else { // le joueur veut recommencer
            quit = false;
            restart = false;
            game_over = false;
            delwin(popup);
            score = 0;
            wclear(window);
            
            delete_message();
            matrix.init_matrix();
            draw_start();
            draw_square(4);
            matrix.new_number();
            draw_arrows(NONE);
            wrefresh(window);
        }
    }
    else if (input_key == 'n' || input_key == 'N'){ // le joueur a répondu "non"
        game_over = false;
        quit = false;
        restart = false;
        
        delwin(popup);
        
        for (int i = 21; i < 27; i++) {
            mvaddstr(i, 40, "                                                          ");
        }
    }
    return 0;
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
    create_pairs();
    
    wbkgd(stdscr, COLOR_PAIR(1));
    attron(1);
    refresh();
    wrefresh(stdscr);
    
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
    
    mvaddstr(43, xmin, "Copyright © 2019 Cyzu. All rights reserved.");
    draw_start();
    matrix.new_number();
    draw_arrows(NONE);
    
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
            case 'k':
                if (game_over) break;
                matrix.move_up();
                if (movement) {
                    matrix.new_number();
                    movement = false;
                    delete_message();
                    draw_arrows(UP);
                }
                else draw_no_move();
                
                break;
            case KEY_DOWN:
            case 'd':
            case 'j':
                if (game_over) break;
                matrix.move_down();
                if (movement) {
                    matrix.new_number();
                    movement = false;
                    delete_message();
                    draw_arrows(DOWN);
                }
                else draw_no_move();
                break;
            case KEY_LEFT:
            case 's':
            case 'h':
                if (game_over) break;
                matrix.move_left();
                if (movement) {
                    matrix.new_number();
                    movement = false;
                    delete_message();
                    draw_arrows(LEFT);
                }
                else draw_no_move();
                break;
            case KEY_RIGHT:
            case 'f':
            case 'l':
                if (game_over) break;
                matrix.move_right();
                if (movement) {
                    matrix.new_number();
                    movement = false;
                    delete_message();
                    draw_arrows(RIGHT);
                }
                else draw_no_move();
                break;
            default:
                break;
        }
        if (quit && popup('q') == -1) break;
        
        if (matrix.is_fully()){
            draw_game_over();
            game_over = true;
        }
        if (restart){
            popup('r');
//            quit = false;
//            restart = false;
//            game_over = false;
//            score = 0;
//
//            delete_message();
//            matrix.init_matrix();
//            draw_start();
//            matrix.new_number();
//            draw_arrows(NONE);
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
