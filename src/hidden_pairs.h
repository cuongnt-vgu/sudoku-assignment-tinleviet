#pragma once

#include "sudoku.h"

typedef struct {
    Cell *cell1;
    Cell *cell2;
    int num_1;
    int num_2;
} HiddenPair;

int hidden_pairs(SudokuBoard *p_board);
void find_hidden_pairs(Cell **cells, HiddenPair *p_hidden_pairs, int *p_counter);
bool is_in_list_hidden_pairs(HiddenPair *p_array, Cell *p_1, Cell *p_2, int *p_counter);