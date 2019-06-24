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

bool movement = false;

void Matrix::init_mfusion(){
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            mfusion[i][j] = true;
        }
    }
}

void Matrix::set_mfusion(int i, int j){
    mfusion[i][j] = false;
}

bool Matrix::get_mfusion(int i, int j){
    return mfusion[i][j];
}

bool Matrix::is_fully(){
    // Vérifier les cases vides
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (get(i, j) == 0) return false;
            
        }
    }
    // Vérifier les valeurs adjacentes
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (get(i, j) == get(i+1, j) || get(i, j) == get(i, j+1)) return false;
        }
    }
    // Vérifier dernière case
    if (get(3, 3) == get(2, 3) || get(3, 3) == get(3, 2)) return false;
    return true;
}

Matrix::Matrix(){
    std::srand((unsigned int)time(NULL));
    for (int i = 0; i < 4; i++){
        for (int j = 0; j < 4; j++){
            matrix[i][j] = 0;
        }
    }
    init_mfusion();
//    matrix[0][0] = 1;
//    matrix[0][2] = 1;
//    matrix[1][0] = 3;
//    matrix[1][1] = 1;
//    matrix[1][2] = 1;
//    matrix[1][3] = 1;
//    matrix[2][0] = 1;
//    matrix[2][1] = 1;
//    matrix[2][2] = 1;
//    matrix[2][3] = 1;
}

int Matrix::get_pow(int i, int j){
    return (int) pow(2, matrix[i][j]);
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
    
    while (get(i, j) != 0){
        i = std::rand() % 4;
        j = std::rand() % 4;
    }
    
    int two_or_four = std::rand() % 2;
    if(two_or_four == 0) two_or_four = 1;
    else two_or_four = 2;
    
    set(i, j, two_or_four);
}

void Matrix::move_up(){
    for (int colonne = 0; colonne < 4; colonne++) {
        for (int ligne = 0; ligne < 4; ligne++) {
            // Fusion de case côte à côte
            if (ligne > 0 &&
                get(ligne, colonne) > 0 &&
                get(ligne, colonne) == get(ligne - 1, colonne) &&
                get_mfusion(ligne - 1, colonne)){
                    set(ligne - 1, colonne, get(ligne, colonne) + 1);
                    set(ligne, colonne, 0);
                    set_mfusion(ligne - 1, colonne);
                
                movement = true;
            }
            
            // Déplacement cases
            if (get(ligne, colonne) == 0) {
                int inc = ligne;
                while (get(inc, colonne) == 0) inc++;
                
                if(inc < 4){
                    set(ligne, colonne, get(inc, colonne));
                    set(inc, colonne, 0);
                    
                    // Fusion après déplacement
                    if (ligne > 0 &&
                        get(ligne, colonne) > 0 &&
                        get(ligne, colonne) == get(ligne - 1, colonne) &&
                        get_mfusion(ligne - 1, colonne)){
                            set(ligne - 1, colonne, get(ligne, colonne) + 1);
                            set(ligne, colonne, 0);
                            set_mfusion(ligne - 1, colonne);
                    }
                    movement = true;
                }
            }
        }
    }
    init_mfusion();
}
    
void Matrix::move_down(){
    for (int colonne = 0; colonne < 4; colonne++) {
        for (int ligne = 3; ligne > -1; ligne--) {
            // Fusion de case côte à côte
            if (ligne < 3 &&
                get(ligne, colonne) > 0 &&
                get(ligne, colonne) == get(ligne + 1, colonne) &&
                get_mfusion(ligne + 1, colonne)){
                    set(ligne + 1, colonne, get(ligne, colonne) + 1);
                    set(ligne, colonne, 0);
                    set_mfusion(ligne + 1, colonne);
                
                movement = true;
            }
            
            // Déplacement cases
            if (get(ligne, colonne) == 0) {
                int inc = ligne;
                while (get(inc, colonne) == 0) inc--;
                
                if(inc > -1){
                    set(ligne, colonne, get(inc, colonne));
                    set(inc, colonne,0);
                    
                    // Fusion après déplacement
                    if (ligne < 3 &&
                        get(ligne, colonne) > 0 &&
                        get(ligne, colonne) == get(ligne + 1, colonne) &&
                        get_mfusion(ligne + 1, colonne)){
                            set(ligne + 1, colonne, get(ligne, colonne) + 1);
                            set(ligne, colonne, 0);
                            set_mfusion(ligne + 1, colonne);
                    }
                    movement = true;
                }
            }
        }
    }
    init_mfusion();
}

void Matrix::move_left(){
    for (int ligne = 0; ligne < 4; ligne++) {
        for (int colonne = 0; colonne < 4; colonne++) {
            // Fusion de case côte à côte
            if (colonne > 0 &&
                get(ligne, colonne) > 0 &&
                get(ligne, colonne) == get(ligne, colonne - 1) &&
                get_mfusion(ligne, colonne - 1)){
                    set(ligne, colonne - 1, get(ligne, colonne) + 1);
                    set(ligne, colonne, 0);
                    set_mfusion(ligne, colonne - 1);
                
                movement = true;
            }
            
            // Déplacement cases
            if (get(ligne, colonne) == 0) {
                int inc = colonne;
                while (get(ligne, inc) == 0) inc++;

                if(inc < 4){
                    set(ligne, colonne, get(ligne, inc));   // Les case non vide côte à côte
                    set(ligne, inc, 0);                     // L'ancienne case devient vide
                    
                    //fusion après déplacement
                    if (colonne > 0 &&
                        get(ligne, colonne) > 0 &&
                        get(ligne, colonne) == get(ligne, colonne - 1) &&
                        get_mfusion(ligne, colonne - 1)){
                            set(ligne, colonne - 1, get(ligne, colonne) + 1);
                            set(ligne, colonne, 0);
                            set_mfusion(ligne, colonne - 1);
                    }
                    movement = true;
                }
            }
        }
    }
    init_mfusion();
}

void Matrix::move_right(){
    for (int ligne = 0; ligne < 4; ligne++) {
        for (int colonne = 3; colonne > -1; colonne--) {
            // Fusion de case côte à côte
            if (colonne < 3 &&
                get(ligne, colonne) > 0 &&
                get(ligne, colonne) == get(ligne, colonne + 1) &&
                get_mfusion(ligne, colonne + 1)){
                    set(ligne, colonne + 1, get(ligne, colonne) + 1);
                    set(ligne, colonne, 0);
                    set_mfusion(ligne, colonne + 1);
                
                movement = true;
            }
            // Déplacement cases
            if (get(ligne, colonne) == 0){
                int inc = colonne;
                while (get(ligne, inc) == 0) inc--;
                
                if (inc > -1){
                    set(ligne, colonne, get(ligne, inc));
                    set(ligne, inc, 0);
                    
                    //fusion après déplacement
                    if (colonne < 3 &&
                        get(ligne, colonne) > 0 &&
                        get(ligne, colonne) == get(ligne, colonne + 1) &&
                        get_mfusion(ligne, colonne + 1)){
                            set(ligne, colonne + 1, get(ligne, colonne) + 1);
                            set(ligne, colonne, 0);
                            set_mfusion(ligne, colonne + 1);
                    }
                    movement = true;
                }
            }
        }
    }
    init_mfusion();
}
