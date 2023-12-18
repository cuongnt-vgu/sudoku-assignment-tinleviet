#pragma once

#include "sudoku.h"

typedef struct {
    Cell *cell1;
    Cell *cell2;
    int num_1;
    int num_2;
} HiddenPair;

int hidden_pairs(SudokuBoard *p_board);
