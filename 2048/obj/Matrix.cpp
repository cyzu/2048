//
//  Matrix.cpp
//  2048
//
//  Created by Chloé Yukino on 23/03/2019.
//  Copyright © 2019 Cyzu. All rights reserved.
//

#include "Matrix.h"
#include <cstdlib>
#include <ctime>

Matrix::Matrix(){
    std::srand((unsigned int)time(NULL));
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            matrix[i][j] = 0;
        }
    }
    matrix[0][2] = 2;
    matrix[2][0] = 3;
    matrix[3][2] = 1031;
    matrix[3][3] = 105;
}

int Matrix::get(int i, int j){
    return matrix[i][j];
}

void Matrix::set(int i, int j, int v){
    matrix[i][j] = v;
}

void Matrix::new_number(){
    int i = std::rand() % 4;
    int j = std::rand() % 4;
    
    while (matrix[i][j] == 0){
        i = std::rand() % 4;
        j = std::rand() % 4;
    }
    
    int two_or_four = std::rand() % 2;
    if(two_or_four == 0) two_or_four = 2;
    else two_or_four = 4;
    
    matrix[i][j] = two_or_four;
}

void Matrix::move_up(){
    
}
