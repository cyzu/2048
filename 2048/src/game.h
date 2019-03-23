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
void write(int score);
void replace_hight_score(int score);

void draw_square(int size);

int init();
void close();
void run();

#endif /* game_h */
