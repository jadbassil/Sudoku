#include "sudoku.hpp"
#include <iostream>
#include <random>
#include <algorithm>
#include <math.h>

Sudoku::Sudoku(Difficulty _difficulty): difficulty(_difficulty) {
    populateGrid();
    removeNumbers();
    
    switch (difficulty) {
    case EASY: difficultyStr = "Easy"; break;
    case MODERATE: difficultyStr = "Moderate"; break;
    case HARD: difficultyStr = "Hard"; break;
    default: break;
    }

    cerr << "Difficulty is set to: " << difficultyStr << endl;
}

Sudoku::~Sudoku() {

}
 
void Sudoku::populateGrid() {
    
    for(int i = 0; i < N; i++) {
        grid.push_back(vector<int>(N, 0));
    }
    fillDiagonals();
    fillRemaining(0,SQRT);


}

void Sudoku::fillDiagonals() {
    std::random_device rd;
    std::mt19937 g(rd());
    array<int,9> a = {1,2,3,4,5,6,7,8,9};
    shuffle(a.begin(), a.end(), g);

    int ia = 0;

    // Fill diagonals 
    for (int q = 0; q < SQRT; q++) {
        for (int i = SQRT*q; i < SQRT*q+SQRT; i++) {
            for (int j =  SQRT*q; j < SQRT*q+SQRT; j++) {
                grid[i][j] = a[ia];
                ia++;
            }
        }
        ia = 0;
        shuffle(a.begin(), a.end(), g);
    }
}

bool Sudoku::fillRemaining(int i, int j) {

    if(j>= N and i < N) {
        i = i+1;
        j = 0;
    }
        if(i >= N and j >= N) return true;

    // ignore the filled 3X3 matrices at the diagonal
    if(i < SQRT){ if(j < SQRT) j = SQRT;}
    else if(i < N-SQRT and j == int(i/SQRT) * SQRT) j = j + SQRT; // i = 4,5,6
    else if (j == N-SQRT) {
        i = i+1;
        j= 0;
        if(i >= N) return true;
    }

    for(int num=1; num <= N; num++) {
        if(valid(num, i, j)) {
            grid[i][j] = num;
            if(fillRemaining(i, j+1)) 
                return true;
        }
    }
    grid[i][j] = 0;

    return false;

}

bool Sudoku::valid(int n, int row, int col) {
    for(int i=0; i<N; i++) {
        if(grid[row][i] == n) return false;
        
    }

    for(int i=0;i< N; i++) {
        if(grid[i][col] == n) return false;
    }

    for(int i=0;i<SQRT;i++) {
        for(int j=0; j<SQRT;j++) {
            int I = row-row%SQRT + i, J = col-col%SQRT + j;
            if(grid[I][J] == n) return false;
        }
    }
    return true;
}

void Sudoku::printGrid() {
    cout << "Sudoku Grid: " << endl;
    for(auto &row: grid) {
        cout << '\t';
        for(auto &col: row) {
            cout << (col != 0 ? to_string(col): "_") << " ";
        }
        cout << endl;
    }
}

void Sudoku::resetGrid() {
    cerr << "Resetting grid..." << endl;
    for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            grid[i].clear();
        }
    }
    grid.clear();
    populateGrid();
    removeNumbers();
}

void Sudoku::removeNumbers() {
    std::random_device rd;
    std::mt19937 g(rd());
    std::uniform_int_distribution<int> d(0,N-1);
    int n = difficulty;
    while(n > 0) {
        int i = d(g);
        int j = d(g);

        if(grid[i][j] != 0) {
            grid[i][j] = 0;
            n--;
        }
    }
}