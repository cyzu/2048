//
//  game.hpp
//  2048
//
//  Created by Chloé Yukino on 05/03/2019.
//  Copyright © 2019 Cyzu. All rights reserved.
//

#ifndef game_h
#define game_h

void write_score(int score);
void write_high_score(int score);
void replace_hight_score(int score);

void draw_square(int size);
void show_matrix();
void draw_start();
void draw_game_over();
void draw_no_move();
void draw_arrows(int direction);
void delete_message();

void create_pairs();
int popup(char option);

int init();
void close();
void run();

#endif /* game_h */
