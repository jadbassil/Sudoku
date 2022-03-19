#ifndef __SUDOKU__HPP__
#define __SUDOKU__HPP__

#include <vector>
#include <string>

using namespace std;

enum Difficulty {EASY = 20, MODERATE = 40, HARD = 60};

class Sudoku {
private:
    const int N{9};
    const int SQRT{3};
    Difficulty difficulty;
    vector<vector<int>> grid;
    string difficultyStr = "";

    void populateGrid();
    /**
     * @brief fill the 3x3 matrices at the diagonals of the grid
     * 
     */
    void fillDiagonals();
    /**
     * @brief A recursive function that uses backtracking to fill the remaining 3x3 matrices after
     * filling the diagonal's 3x3 matrices
     *
     * @param i row's index
     * @param j column's index
     * @return true
     * @return false
     */
    bool fillRemaining(int i, int j);

    /**
     * @brief check if the number n in Grid[row][column] is valid according to the sudoku rules
     * 
     * @param n 
     * @param row 
     * @param col 
     * @return true 
     * @return false 
     */
    bool valid(int n, int row, int col);

    /**
     * @brief hide numbers by replacing a certain number given by the difficulty
     * 
     */
    void removeNumbers();

public:
    Sudoku(Difficulty _difficulty);
    ~Sudoku();

    /**
     * @brief print the grid on the console
     * 
     */
    void printGrid();
    /**
     * @brief reset the grid to new values
     * 
     */
    void resetGrid();
    
};



#endif