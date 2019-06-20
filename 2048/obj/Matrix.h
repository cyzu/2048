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

class Matrix {
    private :
    int matrix[4][4];
    
    public :
    Matrix();
    int get(int i, int j);
    void set(int i, int j, int v);
    void new_number();
    void move_up();
    void move_down();
    void move_right();
    void move_left();
};

#endif /* Matrix_hpp */
