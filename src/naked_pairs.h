#pragma once

#include "sudoku.h"
typedef struct {
    Cell *cell;
    int candidate1;
    int candidate2;
} UnsetInfo;

int naked_pairs(SudokuBoard *p_board);
void find_naked_pairs(Cell **p_cells, int *p_counter, int *p_unset, UnsetInfo *p_unset_array);