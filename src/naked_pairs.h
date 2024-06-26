#pragma once

#include "sudoku.h"
typedef struct UnsetInfo_impl {
    Cell *cell;
    int candidate1;
    int candidate2;
} UnsetInfo;

typedef struct NakedPair_impl{
    Cell *cell1;
    Cell *cell2;
} NakedPair;

bool is_in_list_naked_pairs(NakedPair *p_array, Cell *p_1, Cell *p_2);
int naked_pairs(SudokuBoard *p_board);
void find_naked_pairs(Cell **p_cells, int *p_counter, int *p_unset, UnsetInfo *p_unset_array, NakedPair *p_naked_pairs);
