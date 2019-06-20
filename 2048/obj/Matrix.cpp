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
#include <math.h>

Matrix::Matrix(){
    std::srand((unsigned int)time(NULL));
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            matrix[i][j] = 0;
        }
    }
    matrix[0][2] = 2;
    matrix[1][0] = 4;
    matrix[2][0] = 3;
    matrix[3][2] = 1;
    matrix[3][3] = 5;
}

int Matrix::get(int i, int j){
    return (int) pow(2, matrix[i][j]);
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
    //TODO fusion de case
    
    for (int colonne = 0; colonne < 4; colonne++) {
        for (int ligne = 0; ligne < 3; ligne++) {
            if (matrix[ligne][colonne] == 0) {
                int inc = ligne;
                while (matrix[inc][colonne] == 0) inc++;
                
                if(inc < 4){
                    matrix[ligne][colonne] = matrix[inc][colonne];
                    matrix[inc][colonne] = 0;
                }
            }
        }
    }
}
    
void Matrix::move_down(){
    //TODO FUSION DE CASE
    for (int colonne = 0; colonne < 4; colonne++) {
        for (int ligne = 3; ligne > 0; ligne--) {
            if (matrix[ligne][colonne] == 0) {
                int inc = ligne;
                while (matrix[inc][colonne] == 0) inc--;
                
                if(inc > -1){
                    matrix[ligne][colonne] = matrix[inc][colonne];
                    matrix[inc][colonne] = 0;
                }
            }
        }
    }
}

void Matrix::move_left(){
    //TODO FUSION DE CASE
    for (int ligne = 0; ligne < 4; ligne++) {
        for (int colonne = 0; colonne < 3; colonne++) {
            if (matrix[ligne][colonne] == 0) {
                int inc = colonne;
                while (matrix[ligne][inc] == 0) inc++;
                
                if(inc < 4){
                    matrix[ligne][colonne] = matrix[ligne][inc];
                    matrix[ligne][inc] = 0;
                }
            }
        }
    }
}

void Matrix::move_right(){
    //TODO
    for (int ligne = 0; ligne < 4; ligne++) {
        for (int colonne = 3; colonne > 0; colonne--) {
            if (matrix[ligne][colonne] == 0){
                int inc = colonne;
                while (matrix[ligne][inc] == 0) inc--;
                
                if (inc > -1){
                    matrix[ligne][colonne] = matrix[ligne][inc];
                    matrix[ligne][inc] = 0;
                }
            }
        }
    }
}
