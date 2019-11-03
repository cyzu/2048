//
//  Matrix.hpp
//  2048
//
//  Created by Chloé Yukino on 23/03/2019.
//  Copyright © 2019 Cyzu. All rights reserved.
//

#ifndef Matrix_hpp
#define Matrix_hpp

#include <stdio.h>

extern bool movement;
extern int score;

class Matrix {
    private :
    int matrix[4][4];
    bool mfusion[4][4]; // Matrice de fusion
    
    void init_mfusion();
    void set_mfusion(int i, int j); // set false
    bool get_mfusion(int i, int j);
    
    public :
    Matrix();
    
    void init_matrix();
    bool is_fully();
    int get(int i, int j); // Return value of matrix
    int get_pow(int i, int j); // Return 2^value
    void set(int i, int j, int v);
    void new_number();
    void move_up();
    void move_down();
    void move_right();
    void move_left();
};

#endif /* Matrix_hpp */
