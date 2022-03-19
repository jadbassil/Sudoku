#include <iostream>
#include "sudoku.hpp"

int main(int argc, char const *argv[])
{
    Sudoku s(MODERATE);
    s.printGrid();
    return 0;
}
